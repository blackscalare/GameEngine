#include "TitleScreen.h"

TitleScreen::TitleScreen()
{
    shouldShow = true;
    fontSizeTitle = 30;
    fontSizeInfo = 20;
    fontSizeDifficulty = 20;
    fontSizeExit = 20;
    titleY = fontSizeTitle + 20;
    infoY = GetScreenHeight() - fontSizeInfo - 20;
    easyY = titleY + 50;
    mediumY = easyY + 20;
    hardY = mediumY + 20;
    exitY = infoY - 50;
    titleText = "Menu Title";
    infoText = "Press enter to start game";
    easyText = "Easy";
    mediumText = "Medium";
    hardText = "Hard";
    exitText = "Exit";
}

int TitleScreen::Show()
{
    int selectedMenuItem = 0;
    while (shouldShow) {
        ClearBackground(BLACK);

        BeginDrawing();

        SetSelectedDifficulty(selectedMenuItem);
        
        DrawText(titleText, Tools::Text::CenterTextX(titleText, fontSizeTitle), fontSizeTitle + 20, fontSizeTitle, RAYWHITE);

        DrawText(easyText, Tools::Text::CenterTextX(easyText, fontSizeDifficulty), easyY, fontSizeDifficulty, RAYWHITE);
        DrawText(mediumText, Tools::Text::CenterTextX(mediumText, fontSizeDifficulty), mediumY, fontSizeDifficulty, RAYWHITE);
        DrawText(hardText, Tools::Text::CenterTextX(hardText, fontSizeDifficulty), hardY, fontSizeDifficulty, RAYWHITE);

        DrawText(exitText, Tools::Text::CenterTextX(exitText, fontSizeExit), exitY, fontSizeExit, RAYWHITE);
        DrawText(infoText, Tools::Text::CenterTextX(infoText, fontSizeInfo), infoY, fontSizeInfo, RAYWHITE);

        if (IsKeyPressed(KEY_ENTER)) {
            if (selectedMenuItem == 3) {
                return 1;
            }
            shouldShow = false;
            Settings::difficultySetting = static_cast<DifficultySetting>(selectedMenuItem);
        }

        if (IsKeyPressed(KEY_DOWN)) {
            if (selectedMenuItem < 3) {
                selectedMenuItem++;
            }
        }
        
        if (IsKeyPressed(KEY_UP)) {
            if (selectedMenuItem > 0) {
                selectedMenuItem--;
            }
        }

        EndDrawing();
    }

    return 0;
}

void TitleScreen::SetSelectedDifficulty(int selectedDifficulty)
{
    switch (selectedDifficulty) {
    case 0:
        easyText = ">Easy";
        mediumText = "Medium";
        hardText = "Hard";
        exitText = "Exit";
        break;
    case 1:
        easyText = "Easy";
        mediumText = ">Medium";
        hardText = "Hard";
        exitText = "Exit";
        break;
    case 2:
        easyText = "Easy";
        mediumText = "Medium";
        hardText = ">Hard";
        exitText = "Exit";
        break;
    case 3:
        easyText = "Easy";
        mediumText = "Medium";
        hardText = "Hard";
        exitText = ">Exit";
    }
}