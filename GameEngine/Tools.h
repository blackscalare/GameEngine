#pragma once
#include "raylib.h"

namespace Tools
{
	class Text {
	public:
		int static CenterTextX(const char* text, int fontSize);
		int static CenterTextY(const char* text, int fontSize);
	};
}

