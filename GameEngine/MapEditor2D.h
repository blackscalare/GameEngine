#pragma once
#include "Scene.h"
#include <vector>

class MapEditor2D : public Scene
{
public:
	enum ObjectType {
		WALL
	};

	struct Object {
		ObjectType type;
		Vector2 position;
		int weight;
		int health;
	};

	MapEditor2D();
	int Show();
private:
	bool shouldShow;
	Object wallObject = { WALL, NULL, 99, 99 };
	std::vector<Object> objectVector;

	void PlaceObject(Vector2 position, Object object);
	bool NotInGUIArea(Vector2 mousePos);
	void DrawGridOnSurface();
};

