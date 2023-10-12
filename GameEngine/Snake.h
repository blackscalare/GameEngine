#pragma once
#include <vector>
#include "Position.h"

class Snake
{
public:
	std::vector<Position*> parts;
	int width = 10;
	int height = 10;
};

