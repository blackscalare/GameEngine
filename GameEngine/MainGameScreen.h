#pragma once
#include "Scene.h"
#include "Snake.h"
#include "Food.h"
#include "Structs.h"

class MainGameScreen : public Scene
{
public:
	MainGameScreen();
	int Show() override;
	void HandleKeyPress();
	bool SnakeHasCollided();
	bool SnakeCanEatFood(Position food);
	void SpawnFood();
	void AddSnakePart();
	bool PerformedInvalidMovement(Position currentPosition, Position previousPosition);
private:
	bool isRunning;
	CurrentDirection currentDirection;
	CurrentDirection previousDirection;
	Snake snake;
	Food food;
	int score;
	int moveSpeed;
};

