#pragma once

enum DifficultySetting {
	EASY,
	MEDIUM,
	HARD
};

class Settings {
public:
	static DifficultySetting difficultySetting;
	static float fovY;
};