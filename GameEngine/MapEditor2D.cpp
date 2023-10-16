#include <iostream>
#include "MapEditor2D.h"

#define MENU_HEIGHT 30
#define OBJECT_WIDTH 15
#define OBJECT_HEIGHT 15
#define MAP_OFFSET 10

MapEditor2D::MapEditor2D()
{
    shouldShow = true;
}

int MapEditor2D::Show()
{
    const char* menuItems[] = { "Save", "Undo", "Redo", "Exit" };
    int numMenuItems = sizeof(menuItems) / sizeof(menuItems[0]);

    int selectedMenuItem = -1;
    Object selectedObject = wallObject;

    while (shouldShow) {
        for (int i = 0; i < numMenuItems; ++i) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                Vector2 mousePos = GetMousePosition();
                Rectangle menuItemRect = { i * (GetScreenWidth() / numMenuItems), 0, GetScreenWidth() / numMenuItems, MENU_HEIGHT };
                if (CheckCollisionPointRec(mousePos, menuItemRect)) {
                    switch (i) {
                    case 0:
                        break;
                    case 1:
                        break;
                    case 2:
                        break;
                    case 3:
                        CloseWindow();
                        return 0;
                        break;
                    }
                    selectedMenuItem = i;
                }
               PlaceObject(mousePos, selectedObject);
            }
            if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
                selectedMenuItem = -1;
            }
        }

        BeginDrawing();
        ClearBackground(DARKGRAY);


        DrawGridOnSurface();

        for (int i = 0; i < numMenuItems; ++i) {
            Color c = WHITE;
            if (i == selectedMenuItem) c = RED;
            DrawRectangle(i * (GetScreenWidth() / numMenuItems), 0, GetScreenWidth() / numMenuItems, MENU_HEIGHT, c);
            DrawText(menuItems[i], i * (GetScreenWidth() / numMenuItems) + 10, 5, 20, BLACK);
        }

        for (Object o : objectVector) {
            switch (o.type) {
            case WALL:
                DrawRectangle(o.position.x, o.position.y, OBJECT_WIDTH, OBJECT_HEIGHT, BLACK);
                break;
            }
        }

        EndDrawing();
    }

    return 0;
}

void MapEditor2D::PlaceObject(Vector2 position, Object object)
{
    for (int x = MAP_OFFSET; x < GetScreenWidth() - MAP_OFFSET; x += OBJECT_WIDTH) {
        for (int y = MENU_HEIGHT + MAP_OFFSET; y < GetScreenHeight() - MAP_OFFSET; y += OBJECT_HEIGHT) {
            if(CheckCollisionPointRec(position, Rectangle{ (float)x, (float)y, OBJECT_WIDTH, OBJECT_HEIGHT })) {
                printf("Pressed grid (%d, %d)\n", x, y);
                object.position = Vector2{ (float)x, (float)y };
                objectVector.push_back(object);
            }
        }
    }
}

bool MapEditor2D::NotInGUIArea(Vector2 mousePos)
{
    bool isWithinYRange = mousePos.y > 0 && mousePos.y <= MENU_HEIGHT;
    bool isWithinXRange = mousePos.x > 0 && mousePos.x <= GetScreenWidth();
    return !(isWithinYRange && isWithinXRange);
}

void MapEditor2D::DrawGridOnSurface()
{
    for (int x = MAP_OFFSET; x < GetScreenWidth() - MAP_OFFSET; x += OBJECT_WIDTH) {
        for (int y = MENU_HEIGHT + MAP_OFFSET; y < GetScreenHeight() - MAP_OFFSET; y += OBJECT_HEIGHT) {
            DrawRectangleLines(x, y, OBJECT_WIDTH, OBJECT_HEIGHT, BLACK);
        }
    }
}
