#include "Settings.h"
#include <iostream>
Settings::Settings()
{
	difficultySetting = EASY;
}

void Settings::SetDifficultySetting(DifficultySetting difficultySetting)
{
	std::cout << "Difficulty setting: " << difficultySetting << std::endl;
	this->difficultySetting = difficultySetting;
}

DifficultySetting Settings::GetDifficultySetting()
{
	return difficultySetting;
}
