#include "TitleScreen.h"

TitleScreen::TitleScreen()
{
    shouldShow = true;
    fontSizeTitle = 50;
    fontSizeInfo = 30;
    title = "Menu Title";
    info = "Press enter to start game";
}

int TitleScreen::Show()
{
    while (shouldShow) {
        ClearBackground(BLACK);

        BeginDrawing();

        DrawText(title, Tools::Text::CenterTextX(title, fontSizeTitle), fontSizeTitle + 20, fontSizeTitle, RAYWHITE);
        DrawText(info, Tools::Text::CenterTextX(info, fontSizeInfo), GetScreenHeight() - fontSizeInfo - 200, fontSizeInfo, RAYWHITE);
        
        if (IsKeyPressed(KEY_ENTER)) {
            shouldShow = false;
        }

        EndDrawing();
    }

    return 0;
}
