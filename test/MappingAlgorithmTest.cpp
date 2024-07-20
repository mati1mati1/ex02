#include "gtest/gtest.h"
#include <filesystem>
#include <VacuumSimulator.hpp>
#include <MappingAlgorithm/MappingAlgorithm.hpp>
#include "Logger.hpp"
class MappingAlgorithmTest : public ::testing::Test {
    protected:
        void StartTest(std::filesystem::path inputfile)
        {
            Logger::getInstance().setLogFile("/tmp/myrobot/test.log");
            VacuumSimulator simulator;
            auto config = std::make_shared<MappingAlgorithmConfig>();
            simulator.setAlgorithm(config);
            simulator.readHouseFile(inputfile);
            record = simulator.calculate();
            ASSERT_EQ(record->last()->getLocationType(), LocationType::CHARGING_STATION);
        }
        std::shared_ptr<CleaningRecord> record;
        

};
class FutileTest : public MappingAlgorithmTest {};
class MappingTest : public MappingAlgorithmTest {};
class CleaningTest : public MappingAlgorithmTest {};

TEST_F(FutileTest, minHouse) {
    StartTest("../test/examples/futileTest/house-minvalid.txt");
    ASSERT_EQ(record->size(), 0);
}
TEST_F(FutileTest, tooLittleBatteryToDoAnythingUseful){
    StartTest("../test/examples/futileTest/house-return-small-battery.txt");
    ASSERT_EQ(record->size(), 0);
}
TEST_F(FutileTest, houseLockedinWithDirt){
    StartTest("../test/examples/futileTest/house-closedin2.txt");
    ASSERT_EQ(record->size(), 0);
}
TEST_F(FutileTest, houseMax0){
    StartTest("../test/examples/futileTest/house-max0.txt");
    ASSERT_EQ(record->size(), 0);
}
TEST_F(FutileTest, closedInHouse) {
    StartTest("../test/examples/futileTest/house-closedin.txt");
    ASSERT_EQ(record->size(), 0);
}
TEST_F(MappingTest, lineHouseSomeUnmappable){
    StartTest("../test/examples/mappingTest/house-linemappable-not-cleanable.txt");
    ASSERT_NE(record->size(), 0);
    ASSERT_NE(record->size(), 1000);
    ASSERT_EQ(record->last()->getDirtLevel(), 9);

}

TEST_F(MappingTest, cleanHouse) {
    StartTest("../test/examples/futileTest/house-nodirt.txt");
    ASSERT_NE(record->size(), 0);
    ASSERT_NE(record->size(), 100);
}
TEST_F(MappingTest, lineHouse) {
    StartTest("../test/examples/futileTest/house-line.txt");
    ASSERT_NE(record->size(), 0);
    ASSERT_NE(record->size(), 1000);
    ASSERT_EQ(record->last()->getDirtLevel(), 9);
}

TEST_F(MappingTest, bigEmptyWithReturningToChargeSomeUnmappble){
    StartTest("../test/examples/mappingTest/house-bigEmpty-someUnmappable.txt");
    ASSERT_NE(record->size(), 0);
    ASSERT_NE(record->size(), 100000);
    ASSERT_EQ(record->last()->getDirtLevel(), 0);
}
TEST_F(MappingTest, bigEmptyWithReturningToChargeAllDiscoverable){
    StartTest("../test/examples/mappingTest/house-bigEmpty.txt");
    ASSERT_NE(record->size(), 0);
    ASSERT_NE(record->size(), 100000);
    ASSERT_EQ(record->last()->getDirtLevel(), 0);
}
TEST_F(MappingTest, bigEmptyWithReturningToChargeSomeUnDiscoverable){
    StartTest("../test/examples/mappingTest/house-bigEmpty-allFoundButSomeUndiscoverable.txt");
    ASSERT_NE(record->size(), 0);
    ASSERT_NE(record->size(), 100000);
    ASSERT_EQ(record->last()->getDirtLevel(), 0);
}
TEST_F(CleaningTest, house){
    StartTest("../test/examples/cleaningTest/house.txt");
    ASSERT_NE(record->size(), 0);
    ASSERT_EQ(record->size(), 10);
    ASSERT_EQ((*record)[0]->getDirtLevel(),26);
    ASSERT_LT(record->last()->getDirtLevel(), 26);
}
TEST_F(CleaningTest, houseCorridors){
    StartTest("../test/examples/cleaningTest/house-coridors.txt");
    ASSERT_NE(record->size(), 0);
    ASSERT_LT(record->size(), 100);
    ASSERT_EQ(record->last()->getDirtLevel(), 0);
}
TEST_F(CleaningTest, houseCorridorsWithEmptyRows){
    StartTest("../test/examples/cleaningTest/house-empty-rows-counted-as-corridors.txt");
    ASSERT_NE(record->size(), 0);
    ASSERT_LT(record->size(), 10);
    ASSERT_EQ(record->last()->getDirtLevel(), 0);
}
TEST_F(CleaningTest, houseMaxSteps){
    StartTest("../test/examples/cleaningTest/house-maxsteps.txt");
    ASSERT_NE(record->size(), 0);
    ASSERT_EQ(record->size(), 5);
    ASSERT_EQ(record->last()->getDirtLevel(), 6);
}
TEST_F(CleaningTest, littleBattery){
    StartTest("../test/examples/cleaningTest/house-return-small-battery2.txt");
    ASSERT_NE(record->size(), 0);
    ASSERT_LT(record->size(), 200);
    ASSERT_EQ(record->last()->getDirtLevel(), 0);
}

TEST_F(CleaningTest, narrowHouse){
    StartTest("../test/examples/cleaningTest/house-narrow.txt");
    ASSERT_NE(record->size(), 0);
    ASSERT_LT(record->size(), 20);
    ASSERT_EQ(record->last()->getDirtLevel(), 0);
}
TEST_F(CleaningTest, housePartial){
    StartTest("../test/examples/cleaningTest/house-partial.txt");
    ASSERT_NE(record->size(), 0);
    ASSERT_NE(record->size(), 1000);
    ASSERT_GT((*record)[0]->getDirtLevel(),17);
    ASSERT_EQ(record->last()->getDirtLevel(), 17);
}
TEST_F(CleaningTest, houseSparse){
    StartTest("../test/examples/cleaningTest/house-sparse.txt");
    ASSERT_GT((*record)[0]->getDirtLevel(),100);
    ASSERT_EQ(record->last()->getDirtLevel(), 0);
}
TEST_F(CleaningTest, houseSparse2){
    StartTest("../test/examples/cleaningTest/house-sparse2.txt");
    ASSERT_GT((*record)[0]->getDirtLevel(),10);
    ASSERT_EQ(record->last()->getDirtLevel(), 0);
    ASSERT_NE(record->size(), 0);
    ASSERT_LT(record->size(), 2500);
}
TEST_F(CleaningTest, houseBig){
    StartTest("../test/examples/cleaningTest/house-big.txt");
    ASSERT_GT((*record)[0]->getDirtLevel(),200);
    ASSERT_EQ(record->last()->getDirtLevel(), 0);
    ASSERT_NE(record->size(), 0);
    ASSERT_LT(record->size(), 10000);
    std::cout << record->size() << std::endl;
}
TEST_F(CleaningTest, houseBig1){
    StartTest("../test/examples/cleaningTest/house-big-1.txt");
    ASSERT_GT((*record)[0]->getDirtLevel(),1000);
    ASSERT_EQ(record->last()->getDirtLevel(), 0);
    ASSERT_NE(record->size(), 0);
    ASSERT_LT(record->size(), 7000);
}