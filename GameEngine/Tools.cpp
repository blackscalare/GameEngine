#include "Tools.h"
#include <iostream>
#include <string>

int Tools::Text::CenterTextX(const char* text, int fontSize)
{
	int textWidth = MeasureText(text, fontSize);
	return (GetScreenWidth() - textWidth) / 2;
}

int Tools::Text::CenterTextY(const char* text, int fontSize)
{
	return (GetScreenHeight() - fontSize) / 2;
}
