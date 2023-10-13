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
	int titleY;
	int infoY;
	int easyY;
	int mediumY;
	int hardY;
	const char* titleText;
	const char* infoText;
	const char* easyText;
	const char* mediumText;
	const char* hardText;

	void SetSelectedDifficulty(int selectedDifficulty);
};

