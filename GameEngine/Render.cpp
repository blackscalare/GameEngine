#include "Render.h"
#include "Tools.h"
#include "TitleScreen.h"
#include "MainGameScreen.h"
#include "_3DScene.h"
#include "MapEditor2D.h"
#include "FirstPersonDemo.h"
#include "RogueLike.h"
#include "Space.h"
#include "Pong.h"

int Render::Start()
{
    InitWindow(WIDTH, HEIGHT, "Game Engine");
    SetTargetFPS(TARGET_FPS);

    //TitleScreen ts = TitleScreen("RogueLike");
    //int returnValue = ts.Show();
    
    //MainGameScreen mgs;
    //_3DScene scne;
    //scne.Show();
    //MapEditor2D mapEditor2D;
    //mapEditor2D.Show();
    //FirstPersonDemo firstPersonDemo;
    //firstPersonDemo.Show();
    //Space space;
    //space.Show();
    Pong pong;
    pong.Show();

    //RogueLike rogueLike;
    //rogueLike.Show();

    
    //if(returnValue != 1)
    //    mgs.Show();

	CloseWindow();

    return 0;
}
