#pragma once
#include "Direction.hpp"

class WallsSensor {
public:
	virtual ~WallsSensor() {}
	virtual bool isWall(Direction d) const = 0;
};


