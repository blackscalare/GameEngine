#pragma once
#include <set>
#include "Position.h"

class Food
{
public:
	std::set<Position> foodObjects;
	int width = 10;
	int height = 10;
};

