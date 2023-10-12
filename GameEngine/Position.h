#pragma once
class Position {
public:
	Position() {};
	Position(int x, int y) { this->x = x; this->y = y; }
	int x;
	int y;

	bool operator<(const Position& other) const {
		return x + y < other.x + other.y;
	}
};