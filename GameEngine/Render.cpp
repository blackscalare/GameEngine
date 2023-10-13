#include "Render.h"
#include "Tools.h"
#include "TitleScreen.h"
#include "MainGameScreen.h"
#include "_3DScene.h"

int Render::Start()
{
    InitWindow(WIDTH, HEIGHT, "Snake Clone");
    SetTargetFPS(TARGET_FPS);

    TitleScreen ts;
    MainGameScreen mgs;
    _3DScene scne;
    scne.Show();

    int returnValue = ts.Show();
    if(returnValue != 1)
        mgs.Show();


	CloseWindow();

    return 0;
}
