#pragma once
#include "AbstractAlgorithm.hpp"
#include "MappingGraph.hpp"
#include <Coordinate.hpp>
#include <HouseLocation.hpp>
class MappingAlgorithm : public AbstractAlgorithm {
public:
    MappingAlgorithm() {};
    ~MappingAlgorithm() override = default;
    void setMaxSteps(std::size_t maxSteps) override {this->maxSteps = maxSteps;};
    void setWallsSensor(const WallsSensor& sensor) override { wallsSensor =&sensor;};
    void setDirtSensor(const DirtSensor& sensor) override { dirtSensor = &sensor;};
    void setBatteryMeter(const BatteryMeter& meter) override { batteryMeter = &meter; maxBattery = batteryMeter->getBatteryState();};
    Step nextStep() override;


private:
    constexpr uint32_t maxReachableDistance() const { return maxBattery / 2 ;};
    constexpr uint32_t maxCleanableDistance() const { return (maxBattery-1) /2 ;};
    const Coordinate<int32_t> CHRAGER_LOCATION = Coordinate<int32_t>(0,0);
    const Coordinate<int32_t>& getChargerLocation() const { return CHRAGER_LOCATION;};
private:
    uint32_t maxBattery = 0;
    uint32_t maxSteps = 0;
    uint32_t stepsTaken = 0;
    uint32_t longestPathLength = 0; 
    uint32_t dirtFound = 0;  
    const BatteryMeter *batteryMeter = nullptr;
    const WallsSensor *wallsSensor = nullptr;
    const DirtSensor* dirtSensor= nullptr;
    MappingGraph noWallGraph;
    Coordinate<int32_t> relativeCoordinates = Coordinate<int32_t>(0,0);
    bool finished = false;
    bool forceEndMappingStage = false;
private:
    Step stepTowardsCharger() const;
    std::optional<Step> getStepTowardsClosestTileToClean() const;
    std::optional<Step> getStepTowardsClosestUnknown() const;
    uint32_t getLengthToCharger() const;
    bool isExistsMappedCleanableTile() const;
    bool isCompletelyMapped() const;
    bool isFullyCharged() const;
    bool mustReturnToCharger() const;
    bool guaranteedReturnToCharger(Step step) const;
    bool isProgressPossible() const;
    bool isKnownCleanableTile(const HouseLocationMapping &locationMapping, BFSResult result) const;
    bool isPotentiallyCleanableTile(const HouseLocationMapping &locationMapping, BFSResult result) const;
    void updateLocationIfExists(const HouseLocation &newLocation);
    Step getStepTowardsDestination(const Coordinate<int32_t>& destination, const std::shared_ptr<std::unordered_map<Coordinate<int32_t>,BFSResult>> results) const;
    bool isSensorsSet() const { return wallsSensor && dirtSensor && batteryMeter;};
    bool isOnCharger() const;
    Step calculateNextStep();
    bool isMappingStage() const;
    void mapDirection(Direction direction);
    void mapSurroundings();
    void mapCurrentLocation();
    void updateLongestPathLength(uint32_t pathLength) {if (pathLength > longestPathLength) {longestPathLength = pathLength;}}
    void updateDirtFound(uint32_t dirt) {dirtFound += dirt;}
};
class MappingAlgorithmConfig : public AlgorithmConfig {
public:
    MappingAlgorithmConfig() { };
    AlgorithmType getType() const override { return AlgorithmType::Mapping; };
    ~MappingAlgorithmConfig() override = default;
};