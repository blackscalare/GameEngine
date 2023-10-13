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
	int fontSizeDifficulty;
	int fontSizeExit;
	int titleY;
	int infoY;
	int easyY;
	int mediumY;
	int hardY;
	int exitY;
	const char* titleText;
	const char* infoText;
	const char* easyText;
	const char* mediumText;
	const char* hardText;
	const char* exitText;

	void SetSelectedDifficulty(int selectedDifficulty);
};

