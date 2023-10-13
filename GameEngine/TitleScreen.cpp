#include "TitleScreen.h"

TitleScreen::TitleScreen()
{
    shouldShow = true;
    fontSizeTitle = 30;
    fontSizeInfo = 20;
    fontSizeDifficulty = 20;
    titleY = fontSizeTitle + 20;
    infoY = GetScreenHeight() - fontSizeInfo - 50;
    easyY = titleY + 50;
    mediumY = easyY + 20;
    hardY = mediumY + 20;
    titleText = "Menu Title";
    infoText = "Press enter to start game";
    easyText = "Easy";
    mediumText = "Medium";
    hardText = "Hard";
}

int TitleScreen::Show()
{
    int selectedDifficulty = 0;
    while (shouldShow) {
        ClearBackground(BLACK);

        BeginDrawing();

        SetSelectedDifficulty(selectedDifficulty);
        
        DrawText(titleText, Tools::Text::CenterTextX(titleText, fontSizeTitle), fontSizeTitle + 20, fontSizeTitle, RAYWHITE);

        DrawText(easyText, Tools::Text::CenterTextX(easyText, fontSizeDifficulty), easyY, fontSizeDifficulty, RAYWHITE);
        DrawText(mediumText, Tools::Text::CenterTextX(mediumText, fontSizeDifficulty), mediumY, fontSizeDifficulty, RAYWHITE);
        DrawText(hardText, Tools::Text::CenterTextX(hardText, fontSizeDifficulty), hardY, fontSizeDifficulty, RAYWHITE);

        DrawText(infoText, Tools::Text::CenterTextX(infoText, fontSizeInfo), GetScreenHeight() - fontSizeInfo - 50, fontSizeInfo, RAYWHITE);

        if (IsKeyPressed(KEY_ENTER)) {
            shouldShow = false;
            settings->SetDifficultySetting(static_cast<DifficultySetting>(selectedDifficulty));
        }

        if (IsKeyPressed(KEY_DOWN)) {
            if (selectedDifficulty < 2) {
                selectedDifficulty++;
            }
        }
        
        if (IsKeyPressed(KEY_UP)) {
            if (selectedDifficulty > 0) {
                selectedDifficulty--;
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
        break;
    case 1:
        easyText = "Easy";
        mediumText = ">Medium";
        hardText = "Hard";
        break;
    case 2:
        easyText = "Easy";
        mediumText = "Medium";
        hardText = ">Hard";
        break;
    }
}