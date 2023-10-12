#pragma once
#include "Scene.h"
#include "Snake.h"
#include "Food.h"

enum CurrentDirection
{
	UP,
	RIGHT,
	LEFT,
	DOWN
};

class MainGameScreen : public Scene
{
public:
	MainGameScreen();
	int Show() override;
	void HandleKeyPress();
	bool SnakeHasCollided();
	bool SnakeCanEatFood(Position food);
	void SpawnFood(Snake snake);
	void AddSnakePart();
	bool Did180Turn();
private:
	bool isRunning;
	CurrentDirection currentDirection;
	CurrentDirection previousDirection;
	Snake snake;
	Food food;
	int score;
};

