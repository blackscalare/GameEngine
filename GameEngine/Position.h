#pragma once
class Position {
public:
	// Creates a point outisde visible range
	Position() { x = -100; y = -100; };
	Position(int x, int y) { this->x = x; this->y = y; }
	int x;
	int y;

	bool operator<(const Position& other) const {
		return x + y < other.x + other.y;
	}

	bool operator==(const Position& other) const {
		return x == other.x && y == other.y;
	}
};