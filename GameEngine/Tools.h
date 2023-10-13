#pragma once
#include "raylib.h"
#include "Structs.h"
#include <string>

namespace Tools
{
	class Text {
	public:
		int static CenterTextX(const char* text, int fontSize);
		int static CenterTextY(const char* text, int fontSize);
	};

	class Draw {
	public:
		void static DrawGrid();
	};

	class Debug {
	public:
		std::string static DirectionToString(CurrentDirection direction);
	};
}

