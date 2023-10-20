#include "Space.h"

Space::Space()
{
	running = true;
}

int Space::Show()
{
	Camera camera = { 0 };
	camera.position = Vector3{ 0.2f, 0.4f, 0.2f };    // Camera position
	camera.target = Vector3{ 0.185f, 0.4f, 0.0f };    // Camera looking at point
	camera.up = Vector3{ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
	camera.fovy = Settings::fovY;                                // Camera field-of-view Y
	camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type
	Vector3 position = { 0.0f, 0.0f, 0.0f };            // Set model position

	Image imMap = LoadImage("resources/cubicmap.png");
	Texture2D cubicmap = LoadTextureFromImage(imMap);
	Mesh mesh = GenMeshCubicmap(imMap, { 1.0f, 1.0f, 1.0f });
	Model model = LoadModelFromMesh(mesh);

	// NOTE: By default each cube is mapped to one part of texture atlas
	Texture2D texture = LoadTexture("resources/cubicmap_atlas.png");    // Load map texture
	model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;    // Set map diffuse texture
	
	// Get map image data to be used for collision detection
	Color* mapPixels = LoadImageColors(imMap);
	UnloadImage(imMap);

	Vector3 mapPosition = { -16.0f, 0.0f, -8.0f };
	DisableCursor();


	while (running) {
		Vector3 oldCamPos = camera.position;
		UpdateCamera(&camera, CAMERA_FIRST_PERSON);

		Vector2 playerPos = { camera.position.x, camera.position.z };
		float playerRadius = 0.1f;

		int playerCellX = (int)(playerPos.x - mapPosition.x + 0.5f);
		int playerCellY = (int)(playerPos.y - mapPosition.y + 0.5f);
		
		// OOB checks
		if (playerCellX < 0) playerCellX = 0;
		else if (playerCellX >= cubicmap.width) playerCellX = cubicmap.width - 1;

		if (playerCellY < 0) playerCellY = 0;
		else if (playerCellY >= cubicmap.height) playerCellY = cubicmap.height - 1;

		// Check map collisions using image data and player position
	   // TODO: Improvement: Just check player surrounding cells for collision
		for (int y = 0; y < cubicmap.height; y++) {
			for (int x = 0; x < cubicmap.width; x++) {
				if ((mapPixels[y * cubicmap.width + x].r == 255) &&       // Collision: white pixel, only check R channel
					(CheckCollisionCircleRec(playerPos, playerRadius,
						Rectangle {
					mapPosition.x - 0.5f + x * 1.0f, mapPosition.z - 0.5f + y * 1.0f, 1.0f, 1.0f
				})))
				{
					// Collision detected, reset camera position
					camera.position = oldCamPos;
				}
			}
		}

		BeginDrawing();
			ClearBackground(BLACK);
		
			BeginMode3D(camera);
				DrawModel(model, mapPosition, 1.0f, WHITE);
			EndMode3D();

			DrawTextureEx(cubicmap, { GetScreenWidth() - cubicmap.width * 4.0f - 20, 20.0f }, 0.0f, 4.0f, WHITE);
			DrawRectangleLines(GetScreenWidth() - cubicmap.width * 4 - 20, 20, cubicmap.width * 4, cubicmap.height * 4, GREEN);

			// Draw player position radar
			DrawRectangle(GetScreenWidth() - cubicmap.width * 4 - 20 + playerCellX * 4, 20 + playerCellY * 4, 4, 4, RED);
		
		EndDrawing();
	}

	UnloadImageColors(mapPixels);   // Unload color array

	UnloadTexture(cubicmap);        // Unload cubicmap texture
	UnloadModel(model);             // Unload map model

	return 0;
}
