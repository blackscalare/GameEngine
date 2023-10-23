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

void Tools::Draw::CenterRectangleX(Rectangle* rectangle)
{
    rectangle->x = (GetScreenWidth() / 2.0f) - (rectangle->width / 2);
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

bool Tools::Vector::EraseVector2FromElement(const Vector2& element, const Vector2& rangeStart, const Vector2& rangeEnd)
{
    return (element.x >= rangeStart.x && element.x <= rangeEnd.x) &&
        (element.y >= rangeStart.y && element.y <= rangeEnd.y);
}

bool Tools::Vector::ValuesAreNull(const Vector2& vec)
{
    return vec.x == NULL && vec.y == NULL;
}

bool Tools::String::StringsAreEqual(const char* str1, const char* str2)
{
    return strcmp(str1, str2) == 0;
}
