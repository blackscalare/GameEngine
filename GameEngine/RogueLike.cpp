#include "RogueLike.h"

#define cellSize 10

RogueLike::RogueLike()
{
	isRunning = true;
}

int RogueLike::Show()
{
	GenerateMap();
	while (isRunning) {
		BeginDrawing();
		ClearBackground(BLACK);

		//BeginMode2D(camera);

		//EndMode2D();

		for (Vector2 obstacle : obstacles) {
			DrawRectangle(obstacle.x, obstacle.y, cellSize, cellSize, WHITE);
		}

		EndDrawing();
	}

	return 0;
}

void RogueLike::GenerateMap()
{
	int roomsOnMap = 0;
	switch (Settings::difficultySetting) {
	case EASY:
		roomsOnMap = 3;
		break;
	case MEDIUM:
		roomsOnMap = 4;
		break;
	case HARD:
		roomsOnMap = 5;
	}

	RoomType startRoomType = static_cast<RoomType>(GetRandomValue(0, numStartRoomTypes));

	for (int i = 0; i < roomsOnMap; ++i) {
		RoomType roomType = static_cast<RoomType>(GetRandomValue(numStartRoomTypes, numStartRoomTypes + numRoomTypes));
	}
	
	InitializeRooms();

}

// Should take input on which room to initialize so not all rooms are initialized and take space for no reason
// Or initialize all rooms once and save them to files so they can be loaded when needed <---
void RogueLike::InitializeRooms()
{
	for (const char* roomName : roomFileNames) {
		std::ifstream file(roomName, std::ios::in | std::ios::binary);
		if (!file.good()) {
			file.close();
			GenerateRoom(roomName);
		}
		else {
			Room room;
			file.read(reinterpret_cast<char*>(&room), sizeof(Room));
			file.close();
			rooms.push_back(room);
			for (int x = room.topWallStart.x; x < room.topWallEnd.x; x += cellSize) {
				obstacles.insert(Vector2{ (float)x, room.topWallStart.y });
			}

			for (int x = room.bottomWallStart.x; x < room.bottomWallEnd.x; x += cellSize) {
				obstacles.insert(Vector2{ (float)x, room.bottomWallStart.y });
			}

			for (int y = room.rightWallStart.y; y < room.rightWallEnd.y; y += cellSize) {
				obstacles.insert(Vector2{ room.rightWallStart.x, (float)y });
			}

			for (int y = room.leftWallStart.y; y < room.leftWallEnd.y; y += cellSize) {
				obstacles.insert(Vector2{ room.leftWallStart.y, (float)y });
			}
		}
	}
}

void RogueLike::GenerateRoom(const char* roomName)
{
	RoomType roomToGenerate = roomTypeMap[roomName];

	int roomWidth;
	int roomHeight;
	Vector2 leftWallStart;
	Vector2 leftWallEnd;
	Vector2 topWallStart;
	Vector2 topWallEnd;
	Vector2 rightWallStart;
	Vector2 rightWallEnd;
	Vector2 bottomWallStart;
	Vector2 bottomWallEnd;

	Room room;
	SetRoomDimensions(roomToGenerate, &room);
	SetRoomVectors(roomToGenerate, &room);
	SaveRoomToFile(roomName, room);
}

void RogueLike::SetRoomDimensions(RoomType roomType, Room* room)
{
	switch (roomType) {
	case START_EXIT_UP:
	case START_EXIT_RIGHT:
	case START_EXIT_DOWN:
		room->width = 100;
		room->height = 100;
		break;
	case BIG_ROOM_4_EXITS:
		room->width = 300;
		room->height = 300;
		break;
	defualt:
		std::cerr << "Room dimensions could not be set! Room is not implemented" << std::endl;
	}
}

void RogueLike::SetRoomVectors(RoomType roomType, Room* room)
{
	room->leftWallStart = Vector2{ 0, 0 };
	room->leftWallEnd = Vector2{ 0, room->leftWallStart.y + room->height };
	room->topWallStart = Vector2{ room->leftWallStart.x, room->leftWallStart.y };
	room->topWallEnd = Vector2{ room->topWallStart.x + room->width, room->topWallStart.y };
	room->rightWallStart = Vector2{ room->topWallEnd.x, room->topWallEnd.y };
	room->rightWallEnd = Vector2{ room->rightWallStart.x, room->rightWallStart.y + room->height };
	room->bottomWallStart = Vector2{ room->leftWallEnd.x, room->leftWallEnd.y };
	room->bottomWallEnd = Vector2{ room->rightWallEnd.x, room->rightWallEnd.y };
}

//void RogueLike::CreatePassageways(RoomType roomType, Room* room, Vector2* leftWallStart, Vector2* leftWallEnd, Vector2* topWallStart, Vector2* topWallEnd, Vector2* rightWallStart, Vector2* rightWallEnd, Vector2* bottomWallStart, Vector2* bottomWallEnd)
//{
//	Vector2 rightPassagewayStart{ rightWallStart->x, (rightWallStart->y + rightWallEnd->y) / 2 - cellSize };
//	Vector2 rightPassagewayEnd{ rightWallStart->x, (rightWallStart->y + rightWallEnd->y) / 2 + cellSize };
//	Vector2 topPassagewayStart{ (topWallStart->x + topWallEnd->x) / 2 - cellSize, topWallEnd->y };
//	Vector2 topPassagewayEnd{ (topWallStart->x + topWallEnd->x) / 2 + cellSize, topWallEnd->y };
//	Vector2 bottomPassagewayStart{ (bottomWallStart->x + bottomWallEnd->x) / 2 - cellSize, bottomWallEnd->y };
//	Vector2 bottomPassagewayEnd{ (bottomWallStart->x + bottomWallEnd->x) / 2 + cellSize, bottomWallEnd->y };
//
//	Vector2 wallToRemoveStart{NULL, NULL};
//	Vector2 wallToRemoveEnd{NULL, NULL};
//	
//	switch (roomType) {
//	case START_EXIT_UP:
//		wallToRemoveStart = topPassagewayStart;
//		wallToRemoveEnd = topPassagewayEnd;
//		break;
//	case START_EXIT_RIGHT:
//		wallToRemoveStart = rightPassagewayStart;
//		wallToRemoveEnd = rightPassagewayEnd;
//		break;
//	case START_EXIT_DOWN:
//		wallToRemoveStart = bottomPassagewayStart;
//		wallToRemoveEnd = bottomPassagewayEnd;
//		break;
//	default:
//		std::cerr << "Could not create passageways! Room is not implemented" << std::endl;
//	}
//
//	if (Tools::Vector::ValuesAreNull(wallToRemoveStart) || Tools::Vector::ValuesAreNull(wallToRemoveEnd)) {
//		std::cerr << "Null values found in passageway points" << std::endl;
//	}
//
//	room->walls.erase(std::remove_if(room->walls.begin(), room->walls.end(),
//		[&wallToRemoveStart, &wallToRemoveEnd](const Vector2& element) {
//			return Tools::Vector::EraseVector2FromElement(element, wallToRemoveStart, wallToRemoveEnd);
//		}), room->walls.end());
//
//	// Debug
//	//rooms.push_back(*room);
//}

void RogueLike::SaveRoomToFile(const char* roomFileName, Room room)
{
	std::ofstream ofile(roomFileName, std::ios::out | std::ios::binary);
	if (ofile) {
		ofile.write(reinterpret_cast<const char*>(&room), sizeof(Room));
		ofile.close();
	}
	else {
		std::cerr << "Failed to open file for writing" << std::endl;
	}
}
