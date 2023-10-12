#include "Render.h"
#include "Tools.h"
#include "TitleScreen.h"
#include "MainGameScreen.h"

int Render::Start()
{
    InitWindow(WIDTH, HEIGHT, "Snake Clone");
    SetTargetFPS(TARGET_FPS);

    TitleScreen ts;
    MainGameScreen mgs;

    ts.Show();
    mgs.Show();


	CloseWindow();

    return 0;
}
