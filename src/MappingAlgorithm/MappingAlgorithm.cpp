#include "MappingAlgorithm/MappingAlgorithm.hpp"
#include <algorithm>
#include "MappingAlgorithm.hpp"
#include "Step.hpp"
#include <Logger.hpp>
#include <cassert>
#include <memory>
bool MappingAlgorithm::isOnCharger() const
{
    return relativeCoordinates == getChargerLocation();
}
Step MappingAlgorithm::calculateNextStep()
{
    
    mapSurroundings();
    if (!isProgressPossible() && isOnCharger())
    {
        Logger::getInstance().log("Info: Algorithm terminated properly");
        finished = true;
        return Step::Finish;
    }
    if (!isProgressPossible() || mustReturnToCharger())
    {
        Logger::getInstance().log("Warn: No progress possible, returning to charger for termination");
        return stepTowardsCharger();
    }
    if (isOnCharger() && !isFullyCharged())
    {
        Logger::getInstance().log("Info: battery is not full, charging");
        return Step::Stay;
    }
    if (isCompletelyMapped())
    {
        Logger::getInstance().log("Info: House is completely mapped!");
        auto step = getStepTowardsClosestTileToClean();
        assert(step.has_value()); // House is mapped and we haven't terminated, there must be a cleanable tile 
        if(!guaranteedReturnToCharger(*step))
        {
            return stepTowardsCharger();
        }
        return *step;
    }
    std::optional<Step> step;
    updateLongestPathLength(getLengthToCharger());
    if(isMappingStage())
    {
        Logger::getInstance().log("Info: Mapping stage");
        step = getStepTowardsClosestUnknown(); // Should not return nullopt, we checked that house isn't mapped
        assert(step.has_value());
    }
    else
    {
        Logger::getInstance().log("Info: Cleaning stage");
        step = getStepTowardsClosestTileToClean();
        if (!step.has_value())
        {
            Logger::getInstance().log("Warn: No cleanable tiles found, attempting to map new tiles");
            step = getStepTowardsClosestUnknown();
            assert(step.has_value());
        }
        if (dirtSensor->dirtLevel() > 0) {
            updateDirtFound(dirtSensor->dirtLevel());
        }
    }
    assert(step.has_value());
    if (!guaranteedReturnToCharger(*step))
    {
        return dirtSensor->dirtLevel() != 0 ? Step::Stay : stepTowardsCharger();
    }
    return *step;
    
}

[[nodiscard]] Step MappingAlgorithm::nextStep() {
    
    if (!isSensorsSet())
    {
        Logger::getInstance().log("Error: No sensors terminating");
        throw std::runtime_error("Sensors not set, terminating algorithm");
    }
    if (finished)
    {
        Logger::getInstance().log("Warn: Called step on finished algorithm");
        return Step::Finish;

    }
    Step step = calculateNextStep();
    stepsTaken++;
    relativeCoordinates = relativeCoordinates.getStep(step);
    return step;
}
bool MappingAlgorithm::isMappingStage() const {
    double remainingStepsRatio = static_cast<double>(maxSteps - stepsTaken) / maxSteps;
    double longestPathRatio = static_cast<double>(longestPathLength) / maxSteps;
    double dirtCleaningCapacity = maxSteps - stepsTaken - (2 * longestPathLength); 
    double dirtFoundRatio = static_cast<double>(dirtFound) / dirtCleaningCapacity;
    double x = 0.5 * (1 - longestPathRatio) + 0.5 * (1 - dirtFoundRatio);
    
    return (remainingStepsRatio > x) && (longestPathRatio < 0.5) && (dirtFoundRatio < 0.8) && sqrt(maxSteps) > stepsTaken;
}
bool MappingAlgorithm::isFullyCharged() const
{
    return batteryMeter->getBatteryState() == maxBattery || batteryMeter->getBatteryState() >= maxSteps - stepsTaken; 
}
/**
 * Different from returnToCharger if you intend to stay which will not increase your distance the next time
 */
bool MappingAlgorithm::mustReturnToCharger() const
{
    auto [results,iterator]= noWallGraph.bfs_find_first(relativeCoordinates, std::function<bool (const Coordinate<int32_t> &, const BFSResult &)> (
        [&](const Coordinate<int32_t> &coordinate, const BFSResult &){
            return coordinate == getChargerLocation();
        }
    ));
    return iterator->second.getDistance() >= std::min(static_cast<uint32_t>(batteryMeter->getBatteryState()), maxSteps - stepsTaken );
}
bool MappingAlgorithm::guaranteedReturnToCharger(Step step) const
{
    Coordinate<int32_t> nextLocation = relativeCoordinates.getStep(step);
    auto [results,iterator]= noWallGraph.bfs_find_first(nextLocation, std::function<bool (const Coordinate<int32_t> &, const BFSResult &)> (
        [&](const Coordinate<int32_t> &coordinate, const BFSResult &){
            return coordinate == getChargerLocation();
        }
    ));
    return iterator->second.getDistance() <= std::min(static_cast<uint32_t>(batteryMeter->getBatteryState()) - 1, maxSteps - (stepsTaken + 1) );

}
Step MappingAlgorithm::stepTowardsCharger() const
{
    auto [results,iterator]= noWallGraph.bfs_find_first(relativeCoordinates, std::function<bool (const Coordinate<int32_t> &, const BFSResult &)> (
        [&](const Coordinate<int32_t> &coordinate, const BFSResult &){
            return coordinate == getChargerLocation();
        }
    ));
    if(iterator == results->end())
    {
        throw std::runtime_error("Could not find path to charger in BFS results");
    }
    Step step = getStepTowardsDestination(getChargerLocation(),results);
    return step;
}
uint32_t MappingAlgorithm::getLengthToCharger() const
{
    auto [results,iterator]= noWallGraph.bfs_find_first(relativeCoordinates, std::function<bool (const Coordinate<int32_t> &, const BFSResult &)> (
        [&](const Coordinate<int32_t> &coordinate, const BFSResult &){
            return coordinate == getChargerLocation();
        }
    ));
    if(iterator == results->end())
    {
        throw std::runtime_error("Could not find path to charger in BFS results");
    }
    return iterator->second.getDistance();
}
bool MappingAlgorithm::isExistsMappedCleanableTile() const
{
    for (const auto& mapping : noWallGraph.getMappings())
    {
        if(mapping.getHouseLocation().getLocationType() == LocationType::HOUSE_TILE && mapping.getHouseLocation().getDirtLevel() > 0)
        {
            return true;
        }
    }
    return false;
}
std::optional<Step> MappingAlgorithm::getStepTowardsClosestTileToClean() const
{
    if(!isExistsMappedCleanableTile())
    {
        return std::nullopt;
    }
    auto [results,iterator] = noWallGraph.bfs_find_first(relativeCoordinates, std::function<bool (const Coordinate<int32_t> &, const BFSResult &)> (
        [&](const Coordinate<int32_t> &coordinate, const BFSResult &){
            auto locationMapping = noWallGraph.getVertex(coordinate);
            return locationMapping.getHouseLocation().getLocationType() == LocationType::HOUSE_TILE && locationMapping.getHouseLocation().getDirtLevel() > 0;
        }
    ));
    if(iterator == results->end())
    {
        assert(false);
        return std::nullopt;
    }
    Step step = getStepTowardsDestination(iterator->first,results);
    return step;

}
bool MappingAlgorithm::isCompletelyMapped() const
{
    auto [results,iterator] = noWallGraph.bfs_find_first(getChargerLocation(), std::function<bool (const Coordinate<int32_t> &, const BFSResult &)> (
        [&](const Coordinate<int32_t> &coordinate, const BFSResult & bfsResult){
            auto locationMapping = noWallGraph.getVertex(coordinate);
            return isPotentiallyCleanableTile(locationMapping,bfsResult);
        }
    ));
    return iterator == results->end();
}
bool MappingAlgorithm::isProgressPossible() const
{
    auto [results,iterator] = noWallGraph.bfs_find_first(getChargerLocation(), std::function<bool (const Coordinate<int32_t> &, const BFSResult &)> (
        [&](const Coordinate<int32_t> &coordinate, const BFSResult & bfsResult){
            auto locationMapping = noWallGraph.getVertex(coordinate);
            return isKnownCleanableTile(locationMapping,bfsResult) || isPotentiallyCleanableTile(locationMapping,bfsResult);
        }
    ));
    return iterator != results->end();
}
bool MappingAlgorithm::isKnownCleanableTile(const HouseLocationMapping &locationMapping, BFSResult result) const
{
    return locationMapping.getHouseLocation().getLocationType() == LocationType::HOUSE_TILE &&locationMapping.getHouseLocation().getDirtLevel() > 0 && result.getDistance() <= maxCleanableDistance();
}
bool MappingAlgorithm::isPotentiallyCleanableTile(const HouseLocationMapping &locationMapping, BFSResult result) const
{
    return locationMapping.getHouseLocation().getLocationType() == LocationType::UNKNOWN && (result.getDistance() <= maxCleanableDistance());
}
std::optional<Step> MappingAlgorithm::getStepTowardsClosestUnknown() const
{
    auto [results,iterator] = noWallGraph.bfs_find_first(relativeCoordinates, std::function<bool (const Coordinate<int32_t> &, const BFSResult &)> (
        [&](const Coordinate<int32_t> &coordinate, const BFSResult &){
            auto locationMapping = noWallGraph.getVertex(coordinate);
            return locationMapping.getHouseLocation().getLocationType() == LocationType::UNKNOWN;
        }
    ));
    assert(iterator != results->end());
    Step step = getStepTowardsDestination(iterator->first,results);
    return step;
}
Step MappingAlgorithm::getStepTowardsDestination(const Coordinate<int32_t>& destination, const std::shared_ptr<std::unordered_map<Coordinate<int32_t>,BFSResult>> results) const
{
    if (relativeCoordinates == destination)
    {
        return Step::Stay;
    }
    auto vertexIterator = results->find(destination);
    if (vertexIterator == results->end())
    {
        throw std::runtime_error("Could not find path to destinationv in BFS results");
    }
    while (vertexIterator->second.getDistance() != 1)
    {
        auto nextStepCoordinates = vertexIterator->second.getParent();
        if (!nextStepCoordinates)
        {
            throw std::runtime_error("Could not find parent of node that is not root");
        }
        vertexIterator = results->find(*nextStepCoordinates);
        if (vertexIterator == results->end())
        {
            throw std::runtime_error("Could not find parent of node that is not root");
        }
    }
    Direction direction = relativeCoordinates.getDirection((*vertexIterator).first);
    return DirectionTools::toStep(direction);
}
void MappingAlgorithm::mapCurrentLocation()
{
    HouseLocation location = HouseLocation(LocationType::HOUSE_TILE,dirtSensor->dirtLevel());
    updateLocationIfExists(location);
    if (noWallGraph.isVertex(relativeCoordinates))
    {
        return;
    }

    if (isOnCharger())
    {
        location = HouseLocation(LocationType::CHARGING_STATION);
    }
    noWallGraph.addVertex(HouseLocationMapping(relativeCoordinates,location));
}
void MappingAlgorithm::mapDirection(Direction direction)
{
    auto newLocationPair = relativeCoordinates.getDirection(direction);
    HouseLocation location = HouseLocation(LocationType::UNKNOWN);
    if (wallsSensor->isWall(direction))
    {
        location = HouseLocation(LocationType::WALL);
    }
    if (!noWallGraph.isVertex(newLocationPair))
    {
        if (location.getLocationType() != LocationType::WALL)
        {
            noWallGraph.addVertex(HouseLocationMapping(newLocationPair,location));
        }
    }
    /**
     * A vertex may not be new but does need to attach an edge to it as it is dicovered as unknown by another vertex promping the need to attach an edge to it for another location
     */
    if(location.getLocationType() != LocationType::WALL)
    {
        noWallGraph.addEdge(relativeCoordinates,direction);
    }
    
}
void MappingAlgorithm::updateLocationIfExists(const HouseLocation& newLocation)
{
    if (!noWallGraph.isVertex(relativeCoordinates))
    {
        return;
    }
    auto& vertex = noWallGraph.getVertex(relativeCoordinates);
    auto& noWallVertex = noWallGraph.getVertex(relativeCoordinates);
    vertex.update(newLocation);
    noWallVertex.update(newLocation);
    
}
void MappingAlgorithm::mapSurroundings()
{
    mapCurrentLocation();
    mapDirection(Direction::East);
    mapDirection(Direction::West);
    mapDirection(Direction::North);
    mapDirection(Direction::South);
}

