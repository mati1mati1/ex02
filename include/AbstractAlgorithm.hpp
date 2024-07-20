#pragma once
#include <cstddef>
#include "WallsSensor.hpp"
#include "DirtSensor.hpp"
#include "BatteryMeter.hpp"
#include "Step.hpp"

class AbstractAlgorithm {
public:
    virtual ~AbstractAlgorithm() {}
    virtual void setMaxSteps(std::size_t maxSteps) = 0;
    virtual void setWallsSensor(const WallsSensor&) = 0;
    virtual void setDirtSensor(const DirtSensor&) = 0;
    virtual void setBatteryMeter(const BatteryMeter&) = 0;
    virtual Step nextStep() = 0;    
};

enum class AlgorithmType {
    Mapping
};
class AlgorithmConfig{
    public:
        virtual AlgorithmType getType() const = 0 ;
        virtual ~AlgorithmConfig() = default;
};