#include "Tools.h"
#include <iostream>

int Tools::Text::CenterTextX(const char* text, int fontSize)
{
	int textWidth = MeasureText(text, fontSize);
	return (GetScreenWidth() - textWidth) / 2;
}

int Tools::Text::CenterTextY(const char* text, int fontSize)
{
	return (GetScreenHeight() - fontSize) / 2;
}

void Tools::Draw::DrawGrid()
{
    for (int i = 0; i < GetScreenWidth(); i += 10) {
        DrawLine(i, 0, i, GetScreenHeight(), YELLOW);
    }
    for (int i = 0; i < GetScreenHeight(); i += 10) {
        DrawLine(0, i, GetScreenWidth(), i, YELLOW);
    }
}

std::string Tools::Debug::DirectionToString(CurrentDirection direction)
{
    switch (direction) {
    case UP: return "UP";
    case RIGHT: return "RIGHT";
    case DOWN: return "DOWN";
    case LEFT: return "LEFT";
    default: return "";
    }
}
