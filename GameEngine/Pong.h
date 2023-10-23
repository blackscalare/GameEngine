#pragma once
#include <cmath>
#include <string>
#include "Scene.h"
#include "Tools.h"

class Pong : public Scene
{
public:
	struct Character
	{
		Vector2 pos;
	};

	struct Ball
	{
		Vector2 pos;
		Vector2 direction;
	};

	struct CollosionData
	{
		bool collision;
		float angle;
	};

	struct ScoreData
	{
		int playerScore;
		int aiScore;
	};

	Pong();
	int Show() override;
private:
	bool running;
	float ballSpeed;
	float playerSpeed;
	float aiSpeed;
	ScoreData scoreData;

	void HandleInput(Character* player, Character* AI, Ball* ball);
	void DrawCharacters(Character* player, Character* AI);
	void DrawBall(Ball* b);
	void DrawMiddleLine();
	void DrawScore();
	void Initialize(Character* player, Character* AI, Ball* ball, bool hardReset);
	void UpdateBall(Ball* ball, Character* player, Character* AI);
	void UpdateAI(Ball* ball, Character* AI);
	float CalculateBallAngle(Ball* ball, Rectangle* rect);
	void Restart(Character* player, Character* AI, Ball* ball, bool hardReset);
};

