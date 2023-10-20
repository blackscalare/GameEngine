#pragma once
#include <cmath>
#include "Scene.h"
#include "Tools.h"

class Pong : public Scene
{
public:
	struct Character {
		Vector2 pos;
	};

	struct Ball {
		Vector2 pos;
		Vector2 direction;
	};

	Pong();
	int Show() override;
private:
	bool running;
	float ballSpeed;
	float playerSpeed;

	void HandleInput(Character* player);
	void DrawCharacters(Character* player, Character* AI);
	void DrawBall(Ball* b);
	void DrawMiddleLine();
	void DrawScore();
	void Initialize(Character* player, Character* AI, Ball* ball);
	void UpdateBall(Ball* ball, Character* player, Character* AI);
};

