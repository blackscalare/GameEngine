#include <iostream>
#include "MainGameScreen.h"
#include "Position.h"
#include <random>

MainGameScreen::MainGameScreen()
{
    isRunning = true;
    snake.parts.push_back(new Position((GetScreenHeight() - snake.width) / 2, (GetScreenHeight() - snake.height) / 2));
    food.foodObjects.insert(Position(50, 50));
    currentDirection = UP;
}

int MainGameScreen::Show()
{
    int cycles = 0;
    while (isRunning) {
        cycles += 1;
        // spawn food every 30th second
        if (cycles % (15 * 30) == 0) {
            SpawnFood(snake);
            cycles = 0;
        }
        ClearBackground(BLACK);

        BeginDrawing();

        HandleKeyPress();

        char scoreText[32];
        snprintf(scoreText, 32, "%d", score);

        DrawText(scoreText, GetScreenWidth() - MeasureText(scoreText, 30) - 10, 30, 30, GREEN);

        // Only head should be affected by this movement
        // The other parts move to the previous parts location
        /*for (Position* p : snake.parts) {
            switch (currentDirection) {
            case UP:
                p->y -= 10;
                break;
            case RIGHT:
                p->x += 10;
                break;
            case DOWN:
                p->y += 10;
                break;
            case LEFT:
                p->x -= 10;
                break;
            }

            if (SnakeHasCollided(&snake)) {
                isRunning = false;
            }

            DrawRectangle(p->x, p->y, snake.width, snake.height, WHITE);
        }*/
        Position previousPartLocation;
        for (int i = 0; i < snake.parts.size(); ++i) {
            Position* p = snake.parts[i];

            
            if (i == 0) {
                previousPartLocation = *p;
                switch (currentDirection) {
                case UP:
                    p->y -= 10;
                    break;
                case RIGHT:
                    p->x += 10;
                    break;
                case DOWN:
                    p->y += 10;
                    break;
                case LEFT:
                    p->x -= 10;
                    break;
                }

                if (SnakeHasCollided(&snake)) {
                    isRunning = false;
                }
            }
            else {
                int direction = 1;
                switch (currentDirection) {
                case UP:
                    direction = -1;
                    break;
                case RIGHT:
                    direction = -1;
                    break;
                case DOWN:
                    direction = 1;
                    break;
                case LEFT:
                    direction = 1;
                    break;
                }
                p->x = previousPartLocation.x;
                p->y = previousPartLocation.y;
                previousPartLocation = *p;
            }

            std::cout << previousPartLocation.x << " " << previousPartLocation.y << std::endl;

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
                    SpawnFood(snake);

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

bool MainGameScreen::SnakeHasCollided(Snake* snake) {
    for (Position* p : snake->parts) {
        bool hasCollidedWithBorderX = (p->x + snake->width >= GetScreenWidth()) || (p->x - snake->width <= 0);
        bool hasCollidedWithBorderY = (p->y + snake->height >= GetScreenHeight()) || (p->y - snake->height <= 0);
        if (hasCollidedWithBorderX || hasCollidedWithBorderY) {
            return true;
        }
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

void MainGameScreen::SpawnFood(Snake snake)
{
    // Take a position that is far enough away from the snake head but not inside one of the parts
    std::random_device rd;
    std::mt19937 gen(rd());

    bool gotGoodCoords = false;
    while (!gotGoodCoords) {
        int minX = 0 + food.width;
        int maxX = GetScreenWidth() - food.width;
        int minY = 0 + food.height;
        int maxY = GetScreenHeight() - food.height;

        std::uniform_int_distribution<int> distributionX(minX, maxX);
        std::uniform_int_distribution<int> distributionY(minY, maxY);

        int randomX = distributionX(gen);
        int randomY = distributionY(gen);

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
    // check the last parts location, compensate for radius and direction
    Position* p = snake.parts[snake.parts.size() - 1];
    snake.parts.push_back(new Position(p->x + snake.width, p->y + snake.height));
}
