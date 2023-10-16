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

		for (Room r : rooms) {
			for (Vector2 pos : r.walls) {
				DrawRectangle(pos.x, pos.y, cellSize, cellSize, WHITE);
			}
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

	StartRoomType startRoomType = static_cast<StartRoomType>(GetRandomValue(0, numStartRoomTypes));

	for (int i = 0; i < roomsOnMap; ++i) {
		RoomType roomType = static_cast<RoomType>(GetRandomValue(0, numRoomTypes));
	}
	
	InitializeRooms();
}

// Should take input on which room to initialize so not all rooms are initialized and take space for no reason
// Or initialize all rooms once and save them to files so they can be loaded when needed <---
void RogueLike::InitializeRooms()
{
	int screenHeight = GetScreenHeight();
	const int screenWidth = GetScreenWidth();
	/*
		START_EXIT_UP,
		START_EXIT_RIGHT,
		START_EXIT_DOWN,
		START_2_EXITS_UP_RIGHT,
		START_2_EXITS_DOWN_RIGHT,
	*/

	// Start rooms generate in the middle left of the screen 
	int startRoomWidth = 100;
	int startRoomHeight = 100;
	Vector2 leftWallStart = Vector2{ cellSize, (float)(GetScreenHeight() / 2) };
	Vector2 leftWallEnd = Vector2{ cellSize, leftWallStart.y + startRoomHeight };
	Vector2 topWallStart = Vector2{ leftWallStart.x, leftWallStart.y };
	Vector2 topWallEnd = Vector2{ topWallStart.x + startRoomWidth, topWallStart.y };
	Vector2 rightWallStart = Vector2{ topWallEnd.x, topWallEnd.y };
	Vector2 rightWallEnd = Vector2{ rightWallStart.x, rightWallStart.y + startRoomHeight };
	Vector2 bottomWallStart = Vector2{ leftWallEnd.x, leftWallEnd.y };
	Vector2 bottomWallEnd = Vector2{ rightWallEnd.x + cellSize, rightWallEnd.y};
	
	Room startRoom;
	
	for (int y = leftWallStart.y; y < leftWallEnd.y; y += cellSize) {
		// If we're generating START_EXIT_UP, leave doorway empty

		int doorwayStart = ((leftWallStart.y + leftWallEnd.y) / 2) - 2;
		int doorwayEnd = ((leftWallStart.y + leftWallEnd.y) / 2) + 2;
		startRoom.walls.push_back(Vector2{ (float)leftWallStart.x, (float)y });
	}

	for (int x = topWallStart.x; x < topWallEnd.x; x += cellSize) {
		startRoom.walls.push_back(Vector2{ (float)x, (float)topWallStart.y });
	}

	for (int y = rightWallStart.y; y < rightWallEnd.y; y += cellSize) {
		startRoom.walls.push_back(Vector2{ (float)rightWallStart.x, (float)y });
	}

	for (int x = bottomWallStart.x; x < bottomWallEnd.x; x += cellSize) {
		startRoom.walls.push_back(Vector2{ (float)x, (float)bottomWallStart.y });
	}

	// Remove the walls that should be the passage way
	//START_EXIT_RIGHT

	Vector2 rightPassagewayStart{ rightWallStart.x, (rightWallStart.y + rightWallEnd.y) / 2 - cellSize };
	Vector2 rightPassagewayEnd{ rightWallStart.x, (rightWallStart.y + rightWallEnd.y) / 2 + cellSize };

	startRoom.walls.erase(std::remove_if(startRoom.walls.begin(), startRoom.walls.end(),
		[&rightPassagewayStart, &rightPassagewayEnd](const Vector2& element) {
			return Tools::Vector::EraseVector2FromElement(element, rightPassagewayStart, rightPassagewayEnd);
		}), startRoom.walls.end());

	rooms.push_back(startRoom);
}