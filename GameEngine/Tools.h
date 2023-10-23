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
		void static CenterRectangleX(Rectangle* rectangle);
	};

	class Vector {
	public:
		bool static EraseVector2FromElement(const Vector2& element, const Vector2& rangeStart, const Vector2& rangeEnd);
		bool static ValuesAreNull(const Vector2& vec);
	};

	class String {
	public:
		bool static StringsAreEqual(const char* str1, const char* str2);
	};

	class Debug {
	public:
		std::string static DirectionToString(CurrentDirection direction);
	};
}

