#pragma once
#include "raylib.h"
#include "Tools.h"
#include "Settings.h"

class Scene
{
public:
	virtual int Show();
	Settings* settings = new Settings();
};

