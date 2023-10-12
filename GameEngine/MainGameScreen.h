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
	bool SnakeHasCollided(Snake* snake);
	bool SnakeCanEatFood(Position food);
	void SpawnFood(Snake snake);
	void AddSnakePart();
private:
	bool isRunning;
	CurrentDirection currentDirection;
	Snake snake;
	Food food;
	int score;
};

