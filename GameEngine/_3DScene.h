#pragma once
#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
class _3DScene
{
public:
	_3DScene();
	int Show();
private:
	void MoveLight(int slot, float x, float y);
	void ComputeShadowVolumeForEdge(int slot, Vector2 sp, Vector2 ep);
	void DrawLightMask(int slot);
	void SetupLight(int slot, float x, float y, float radius);
	bool UpdateLight(int slot, Rectangle* boxes, int count);
	void SetupBoxes(Rectangle* boxes, int* count);
};

