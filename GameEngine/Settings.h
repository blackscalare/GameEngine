#pragma once

enum DifficultySetting {
	EASY,
	MEDIUM,
	HARD
};

class Settings {
public:
	Settings();
	void SetDifficultySetting(DifficultySetting difficultySetting);
	DifficultySetting GetDifficultySetting();
private:
	DifficultySetting difficultySetting;
};