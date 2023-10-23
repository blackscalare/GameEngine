#include "Pong.h"

#define BALL_RADIUS 5
#define CHARACTER_WIDTH 10
#define CHARACTER_HEIGHT 40

Pong::Pong()
{
    running = true;
    ballSpeed = 4.0f;
    playerSpeed = 6.0f;
    aiSpeed = 1.5f;
    scoreData = { 0 };
}

int Pong::Show()
{
    Character player;
    Character AI;
    Ball ball;

    Initialize(&player, &AI, &ball, true);

    while (running) {
        HandleInput(&player, &AI, &ball);
        UpdateBall(&ball, &player, &AI);
        UpdateAI(&ball, &AI);

        ClearBackground(BLACK);

        BeginDrawing();
            DrawMiddleLine();
            DrawScore();
            DrawCharacters(&player, &AI);
            DrawBall(&ball);
        EndDrawing();
    }
    return 0;
}

void Pong::HandleInput(Character* player, Character* AI, Ball* ball)
{
    if (IsKeyDown(KEY_UP)) {
        if(player->pos.y > 0)
            player->pos.y -= playerSpeed;
    }
    else if (IsKeyDown(KEY_DOWN)) {
        if(player->pos.y + CHARACTER_HEIGHT < GetScreenHeight())
            player->pos.y += playerSpeed;
    }
    else if (IsKeyDown(KEY_R)) {
        Restart(player, AI, ball, true);
    }
}

void Pong::DrawCharacters(Character* player, Character* AI)
{
    DrawRectangle(player->pos.x, player->pos.y, CHARACTER_WIDTH, CHARACTER_HEIGHT, WHITE);
    DrawRectangle(AI->pos.x, AI->pos.y, CHARACTER_WIDTH, CHARACTER_HEIGHT, WHITE);
}

void Pong::DrawBall(Ball* b)
{
    DrawCircle(b->pos.x, b->pos.y, BALL_RADIUS, WHITE);
}

void Pong::DrawMiddleLine()
{
    Rectangle middleLineRect = { 0, 0, 10, 10 };
    Tools::Draw::CenterRectangleX(&middleLineRect);

    for (int i = 0; i < GetScreenHeight() - 10; i += 40) {
        middleLineRect.y =  i;
        DrawRectangleRec(middleLineRect, {255, 255, 255, 50});
    }
}

void Pong::DrawScore()
{
    std::string playerScoreString = std::to_string(scoreData.playerScore);
    std::string aiScoreString = std::to_string(scoreData.aiScore);
    int playerScoreStringWidth = MeasureText(playerScoreString.c_str(), 40);
    int aiScoreStringWidth = MeasureText(aiScoreString.c_str(), 40);

    int playerScoreCenter = (GetScreenWidth() / 2) / 2;
    int aiScoreCenter = (GetScreenWidth() / 2) + playerScoreCenter;

    DrawText(playerScoreString.c_str(), playerScoreCenter - playerScoreStringWidth, 30, 40, WHITE);
    DrawText(aiScoreString.c_str(), aiScoreCenter - aiScoreStringWidth, 30, 40, WHITE);
}

void Pong::Initialize(Character* player, Character* AI, Ball* ball, bool hardReset)
{
    // Player position is left wall, middle of the screen
    player->pos = { 0, GetScreenHeight() / 2.0f - CHARACTER_HEIGHT };

    // AI position is right wall, middle of the screen
    AI->pos = { (float)(GetScreenWidth() - CHARACTER_WIDTH), GetScreenHeight() / 2.0f - CHARACTER_HEIGHT };

    // Ball position is in the middle of the screen
    ball->pos = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f - BALL_RADIUS };
    // Ball starts moving towards player at the start
    ball->direction = { -ballSpeed, 0.0f };
    
    if(hardReset)
        scoreData = { 0 };
}

void Pong::UpdateBall(Ball* ball, Character* player, Character* AI)
{
    // Check if ball is OOB on the x axis and handle score
    if (ball->pos.x <= 0 || ball->pos.x >= GetScreenWidth()) {
        if (ball->direction.x < 0) {
            // AI scored
            scoreData.aiScore += 1;
        }
        else if (ball->direction.x > 0) {
            // Player scored
            scoreData.playerScore += 1;
        }

        Restart(player, AI, ball, false);
    }

    bool collided = false;
    CollosionData collisionData = { 0 };
    // Decide which character to check for collision given the direction of the ball
    Rectangle rect;
    if (ball->direction.x < 0) {
        rect = { player->pos.x, player->pos.y, CHARACTER_WIDTH, CHARACTER_HEIGHT };
        if ((ball->pos.x >= rect.x && ball->pos.x <= rect.width) &&
            (ball->pos.y >= rect.y && ball->pos.y <= rect.y + rect.height)) {
            collisionData.collision = true;
            collisionData.angle = CalculateBallAngle(ball, &rect);
        }
    }
    else {
        rect = { AI->pos.x, AI->pos.y, CHARACTER_WIDTH, CHARACTER_HEIGHT };
        if ((ball->pos.x >= rect.x && ball->pos.x <= rect.x + rect.width) &&
            (ball->pos.y >= rect.y && ball->pos.y <= rect.y + rect.height)) {
            collisionData.collision = true;
            collisionData.angle = CalculateBallAngle(ball, &rect);
        }
    }

    // Handle ball roof and floor collision
    if (ball->pos.y <= 0 || ball->pos.y >= GetScreenHeight()) {
        // Invert the y direction
        collisionData.angle = ball->direction.y *= -1.0f;
    }

    // Handle Y axis
    // Top half of character shoots it upwards
    // Bottom half of character shoots it downwards
    if (collisionData.collision) {
        ball->direction.x *= -1.0f;
        ball->direction.y = collisionData.angle;
    }


    //printf("ball: (%d, %d)\n", (int)ball->pos.x, (int)ball->pos.y);
    //printf("player: (%d, %d\n", (int)player->pos.x, (int)player->pos.y);
    ball->pos.x += ball->direction.x;
    ball->pos.y += ball->direction.y;
}

void Pong::UpdateAI(Ball* ball, Character* AI)
{
    // AI follows the balls y-axis
    // The AI should try to hit the ball with its center
    // Get the balls y and move the AI according to its speed into it instead of instantly moving to it
    // Otherwise the AI will always hit the ball
    float aiDesiredPosition = ball->pos.y - (CHARACTER_HEIGHT / 2);
    
    if (aiDesiredPosition > AI->pos.y) {
        // Wants to move down
        AI->pos.y += aiSpeed;
    }
    else if (aiDesiredPosition < AI->pos.y) {
        // Wants to move up
        AI->pos.y -= aiSpeed;
    }
}

float Pong::CalculateBallAngle(Ball* ball, Rectangle* rect)
{
    float centerPos = rect->y + CHARACTER_HEIGHT / 2;

    return (ball->pos.y - centerPos) / 10;
}

void Pong::Restart(Character* player, Character* AI, Ball* ball, bool hardReset)
{
    Initialize(player, AI, ball, hardReset);
}