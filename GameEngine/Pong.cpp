#include "Pong.h"

#define BALL_RADIUS 5
#define CHARACTER_WIDTH 10
#define CHARACTER_HEIGHT 30

Pong::Pong()
{
    running = true;
    ballSpeed = 4.0f;
    playerSpeed = 6.0f;
}

int Pong::Show()
{
    Character player;
    Character AI;
    Ball ball;
    Initialize(&player, &AI, &ball);

    while (running) {
        HandleInput(&player);
        UpdateBall(&ball, &player, &AI);

        ClearBackground(BLACK);

        BeginDrawing();
            DrawMiddleLine();
            DrawCharacters(&player, &AI);
            DrawBall(&ball);
        EndDrawing();
    }
    return 0;
}

void Pong::HandleInput(Character* player)
{
    if (IsKeyDown(KEY_UP)) {
        if(player->pos.y > 0)
            player->pos.y -= playerSpeed;
    }
    else if (IsKeyDown(KEY_DOWN)) {
        if(player->pos.y + CHARACTER_HEIGHT < GetScreenHeight())
            player->pos.y += playerSpeed;
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
}

void Pong::Initialize(Character* player, Character* AI, Ball* ball)
{
    // Player position is left wall, middle of the screen
    player->pos = { 0, GetScreenHeight() / 2.0f - CHARACTER_HEIGHT };

    // AI position is right wall, middle of the screen
    AI->pos = { (float)(GetScreenWidth() - CHARACTER_WIDTH), GetScreenHeight() / 2.0f - CHARACTER_HEIGHT };

    // Ball position is in the middle of the 
    ball->pos = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f - (BALL_RADIUS * 2)  };
    // Ball starts moving towards player at the start
    ball->direction = { -ballSpeed, 0.0f };
}

void Pong::UpdateBall(Ball* ball, Character* player, Character* AI)
{
    bool collided = false;
    // Decide which character to check for collision given the direction of the ball
    Rectangle rect;
    if (ball->direction.x < 0) {
        rect = { player->pos.x ,player->pos.y, CHARACTER_WIDTH, CHARACTER_HEIGHT };
        if ((ball->pos.x >= rect.x && ball->pos.x <= rect.width) &&
            (ball->pos.y >= rect.y && ball->pos.y <= rect.y + rect.height)) {
            collided = true;
        }
    }
    else {
        rect = { AI->pos.x ,AI->pos.y, CHARACTER_WIDTH, CHARACTER_HEIGHT };
        if ((ball->pos.x >= rect.x && ball->pos.x <= rect.x + rect.width) &&
            (ball->pos.y >= rect.y && ball->pos.y <= rect.y + rect.height)) {
            collided = true;
        }
    }

    // Handle Y axis
    // Top half of character shoots it upwards
    // Bottom half of character shoots it downwards
    if(collided)
        ball->direction.x *= -1.0f;


    //printf("ball: (%d, %d)\n", (int)ball->pos.x, (int)ball->pos.y);
    //printf("player: (%d, %d\n", (int)player->pos.x, (int)player->pos.y);
    ball->pos.x += ball->direction.x;
    ball->pos.y += ball->direction.y;
}