#pragma once
#include "Scene.h"
#include "Settings.h"

class Space : public Scene
{
public:
	Space();
	int Show() override;
private:
	bool running;
};

