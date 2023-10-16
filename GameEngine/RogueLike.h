#pragma once
#include <vector>
#include "Scene.h"
#include "Tools.h"
#include "Settings.h"

class RogueLike : public Scene
{
public:
	enum RoomType {
		CORRIDOR_2_EXITS,
		CORRIDOR_3_EXITS,
		BIG_ROOM_4_EXITS
	};

	enum StartRoomType {
		START_EXIT_UP,
		START_EXIT_RIGHT,
		START_EXIT_DOWN,
		START_2_EXITS_UP_RIGHT,
		START_2_EXITS_DOWN_RIGHT,
	};

	struct Room {
		std::vector<Vector2> walls;
	};

	struct Player {
		Vector2 position;
		int health;
	};

	RogueLike();
	int Show() override;
private:
	int GetRoomTypeValueCount() {
		int count = 0;
		for (int i = CORRIDOR_2_EXITS; i <= BIG_ROOM_4_EXITS; ++i) {
			count++;
		}
		return count;
	}

	int GetStartRoomTypeValueCount() {
		int count = 0;
		for (int i = START_EXIT_UP; i <= START_2_EXITS_DOWN_RIGHT; ++i) {
			count++;
		}
		return count;
	}

	bool isRunning;
	int numRoomTypes = GetRoomTypeValueCount();
	int numStartRoomTypes = GetStartRoomTypeValueCount();
	Camera2D camera;
	std::vector<Room> rooms;

	void GenerateMap();
	void InitializeRooms();


};

