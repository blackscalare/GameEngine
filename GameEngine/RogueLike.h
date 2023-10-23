#pragma once
#include <set>
#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include "Scene.h"
#include "Tools.h"
#include "Settings.h"

#define START_ROOM_NAME_1 "start1.room"
#define START_ROOM_NAME_2 "start2.room"
#define START_ROOM_NAME_3 "start3.room"
#define BIG_ROOM_4_NAME "bigroom4.room"

class RogueLike : public Scene
{
public:
	enum RoomType {
		START_EXIT_UP,
		START_EXIT_RIGHT,
		START_EXIT_DOWN,
		CORRIDOR_2_EXITS,
		CORRIDOR_3_EXITS,
		BIG_ROOM_4_EXITS
	};

	struct Room
	{
		int width;
		int height;
		Vector2 topWallStart;
		Vector2 topWallEnd;
		Vector2 rightWallStart;
		Vector2 rightWallEnd;
		Vector2 bottomWallStart;
		Vector2 bottomWallEnd;
		Vector2 leftWallStart;
		Vector2 leftWallEnd;
	};

	struct Player {
		Vector2 position;
		int health;
	};

	struct Vector2Compare {
		bool operator()(const Vector2& a, const Vector2& b) const {
			if (a.x == b.x) {
				return a.y < b.y;
			}
			return a.x < b.x;
		}
	};

	RogueLike();
	int Show() override;
private:
	std::vector<const char*> roomFileNames{ START_ROOM_NAME_1, START_ROOM_NAME_2, START_ROOM_NAME_3, BIG_ROOM_4_NAME };
	bool isRunning;
	int numRoomTypes = 3;
	int numStartRoomTypes = 3;
	Camera2D camera;
	std::vector<Room> rooms;
	std::vector<RoomType> placedRooms;
	std::set<Vector2, Vector2Compare> obstacles;
	std::map<const char*, RoomType> roomTypeMap {
		{
			START_ROOM_NAME_1, START_EXIT_UP
		},
		{
			START_ROOM_NAME_2, START_EXIT_RIGHT
		},
		{
			START_ROOM_NAME_3, START_EXIT_DOWN
		},
		{
			BIG_ROOM_4_NAME, BIG_ROOM_4_EXITS
		}
	};

	void GenerateMap();
	void InitializeRooms();
	void GenerateRoom(const char* roomName);
	void SetRoomDimensions(RoomType roomType, Room* room);
	void SetRoomVectors(RoomType roomType, Room* room);
	//void CreatePassageways(RoomType roomType, Room* room, Vector2* leftWallStart, Vector2* leftWallEnd, Vector2* topWallStart, Vector2* topWallEnd, Vector2* rightWallStart, Vector2* rightWallEnd, Vector2* bottomWallStart, Vector2* bottomWallEnd);
	void SaveRoomToFile(const char* roomFileName, Room room);
};

