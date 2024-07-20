#pragma once
#include <cstddef>


class BatteryMeter {
public:
	virtual ~BatteryMeter() {}
	virtual std::size_t getBatteryState() const = 0;
};
