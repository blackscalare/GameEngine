#include <iostream>
#include "MainGameScreen.h"
#include "Position.h"
#include <random>

#define MOVE_SPEED_EASY 5
#define MOVE_SPEED_MEDIUM 10
#define MOVE_SPEED_HARD 15

MainGameScreen::MainGameScreen()
{
    isRunning = true;
    // Set the head location
    snake.parts.push_back(new Position((GetScreenHeight() - snake.width) / 2, (GetScreenHeight() - snake.height) / 2));
    // Add additional snake parts
    AddSnakePart();
    AddSnakePart();
    // Spawn initial food
    SpawnFood();
    currentDirection = UP;
    moveSpeed = 10;
}

int MainGameScreen::Show()
{
    switch (Settings::difficultySetting) {
    case EASY:
        moveSpeed = MOVE_SPEED_EASY;
        break;
    case MEDIUM:
        moveSpeed = MOVE_SPEED_MEDIUM;
        break;
    case HARD:
        moveSpeed = MOVE_SPEED_HARD;
        break;
    }

    int cycles = 0;
    while (isRunning) {
        cycles += 1;
        // spawn food every 30th second
        if (cycles % (15 * 30) == 0) {
            SpawnFood();
            cycles = 0;
        }
        ClearBackground(BLACK);

        BeginDrawing();

        HandleKeyPress();

        char scoreText[32];
        snprintf(scoreText, 32, "%d", score);

        DrawText(scoreText, GetScreenWidth() - MeasureText(scoreText, 30) - 10, 30, 30, GREEN);

        Position previousPartLocation;
        for (int i = 0; i < snake.parts.size(); ++i) {
            Position* p = snake.parts[i];
                        
            if (i == 0) {
                previousPartLocation = *p;
                // Forbid 180 
                PreventInvalidMovement(*p);
                switch (currentDirection) {
                case UP:
                    p->y -= moveSpeed;
                    break;
                case RIGHT:
                    p->x += moveSpeed;
                    break;
                case DOWN:
                    p->y += moveSpeed;
                    break;
                case LEFT:
                    p->x -= moveSpeed;
                    break;
                }

                if (SnakeHasCollided()) {
                    isRunning = false;
                }
            }
            else {
                Position tmp = *p;
                p->x = previousPartLocation.x;
                p->y = previousPartLocation.y;
                previousPartLocation = tmp;
            }

            DrawRectangle(p->x, p->y, snake.width, snake.height, WHITE);
        }
        
        if (food.foodObjects.size() > 0) {
            for (const Position& p : food.foodObjects) {
                if (SnakeCanEatFood(p)) {
                    score += 10;
                    //add snake part
                    AddSnakePart();

                    food.foodObjects.erase(p);

                    //instantly spawn new food
                    SpawnFood();

                    // Stop iterating and redraw everything
                    break;
                }
                DrawRectangle(p.x, p.y, food.width, food.height, GREEN);

            }
        }
        

        EndDrawing();
    }
    return 0;
}

void MainGameScreen::HandleKeyPress() {
    previousDirection = currentDirection;
    if (IsKeyPressed(KEY_UP)) {
        currentDirection = UP;
    }
    
    if (IsKeyPressed(KEY_RIGHT)) {
        currentDirection = RIGHT;
    }
    
    if (IsKeyPressed(KEY_DOWN)) {
        currentDirection = DOWN;
    }
    
    if (IsKeyPressed(KEY_LEFT)) {
        currentDirection = LEFT;
    }
}

bool MainGameScreen::SnakeHasCollided() {
    // Only check if the head has collided with the wall to prevent issues
    Position* p = snake.parts[0];
    bool hasCollidedWithBorderX = (p->x + snake.width >= GetScreenWidth()) || (p->x - snake.width <= 0);
    bool hasCollidedWithBorderY = (p->y + snake.height >= GetScreenHeight()) || (p->y - snake.height <= 0);
    if (hasCollidedWithBorderX || hasCollidedWithBorderY) {
        return true;
    }
    
    // Check if the head has collided with any other part of the body
    for (int i = 1; i < snake.parts.size(); ++i) {
        Position* bodyP = snake.parts[i];
        if (p->x == bodyP->x && p->y == bodyP->y)
            return true;
    }

    return false;
}

bool MainGameScreen::SnakeCanEatFood(Position foodPosition)
{
    Position snakeHeadPosition = *(snake.parts[0]);

    bool horizontalCollision = (snakeHeadPosition.x < foodPosition.x + food.width) && (snakeHeadPosition.x + snake.width > foodPosition.x);
    bool verticalCollision = (snakeHeadPosition.y < foodPosition.y + food.height) && (snakeHeadPosition.y + snake.height > foodPosition.y);

    return horizontalCollision && verticalCollision;
}

void MainGameScreen::SpawnFood()
{
    // Take a position that is far enough away from the snake head but not inside one of the parts

    bool gotGoodCoords = false;
    while (!gotGoodCoords) {
        int minX = food.width;
        int maxX = GetScreenWidth() - food.width;
        int minY = food.height;
        int maxY = GetScreenHeight() - food.height;

        int randomX = GetRandomValue(minX, maxX);
        int randomY = GetRandomValue(minY, maxY);

        for (Position* p : snake.parts) {
            if ((randomX >= p->x + 30 || randomX <= p->x - 30) && (randomY >= p->y + 30 || randomY <= p->y - 30))
                gotGoodCoords = true;
            else
                gotGoodCoords = false;
        }

        if(gotGoodCoords)
            food.foodObjects.insert(Position(randomX, randomY));
    }
}

void MainGameScreen::AddSnakePart()
{
    Position* p = snake.parts[snake.parts.size() - 1];
    snake.parts.push_back(new Position());
}

void MainGameScreen::PreventInvalidMovement(Position currentPosition)
{
    Position nextPosition = currentPosition;
    Position partBehindHead = *(snake.parts[1]);

    switch (currentDirection) {
    case UP:
        nextPosition.y -= moveSpeed;
        break;
    case RIGHT:
        nextPosition.x += moveSpeed;
        break;
    case DOWN:
        nextPosition.y += moveSpeed;
        break;
    case LEFT:
        nextPosition.x -= moveSpeed;
        break;
    }
    
    if (nextPosition == partBehindHead) {
        currentDirection = previousDirection;
    }
}
