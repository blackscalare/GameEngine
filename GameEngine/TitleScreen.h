#pragma once
#include "Scene.h"
class TitleScreen : public Scene
{
public:
	TitleScreen();
	int Show() override;
private:
	int shouldShow;
	int fontSizeTitle;
	int fontSizeInfo;
	const char* title;
	const char* info;
};

