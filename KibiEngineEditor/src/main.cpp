#include <raylib.h>
#include <raymath.h>

struct Matrix2x2 {
	float a, b, c, d;
};

// ��������������� ��������� ������
struct IsoCamera {
	Vector2 offset;
	float scale;
	float minScale;
	float maxScale;
};

// ���������� ������� �������������� ���������
Vector2 ToScreenCoordinate(Vector2 gridPos, float tileSize, float scale) {
	const float i_x = 1.0f;
	const float i_y = 0.5f;
	const float j_x = -1.0f;
	const float j_y = 0.5f;

	return {
		(gridPos.x * i_x + gridPos.y * j_x) * tileSize * 0.5f * scale,
		(gridPos.x * i_y + gridPos.y * j_y) * tileSize * 0.5f * scale
	};
}

Matrix2x2 InvertMatrix(float a, float b, float c, float d) {
	float det = 1.0f / (a * d - b * c);
	return { det * d, det * -b, det * -c, det * a };
}

Vector2 ToGridCoordinate(Vector2 screenPos, float tileSize, float scale) {
	const float a = 1.0f * 0.5f * tileSize * scale;
	const float b = -1.0f * 0.5f * tileSize * scale;
	const float c = 0.5f * 0.5f * tileSize * scale;
	const float d = 0.5f * 0.5f * tileSize * scale;

	Matrix2x2 inv = InvertMatrix(a, b, c, d);

	return {
		screenPos.x * inv.a + screenPos.y * inv.b,
		screenPos.x * inv.c + screenPos.y * inv.d
	};
}

// ���������� ������� ��������� �����
void DrawIsoRhombus(Vector2 center, float size, float scale, Color color) {
	Vector2 points[4];
	float scaledSize = size * scale;

	points[0] = { center.x, center.y - scaledSize / 2 };
	points[1] = { center.x + scaledSize / 2, center.y };
	points[2] = { center.x, center.y + scaledSize / 2 };
	points[3] = { center.x - scaledSize / 2, center.y };

	DrawLineV(points[0], points[1], color);
	DrawLineV(points[1], points[2], color);
	DrawLineV(points[2], points[3], color);
	DrawLineV(points[3], points[0], color);
}

int main(void) {
	const int screenWidth = 1920;
	const int screenHeight = 1080;
	const int gridSize = 20;
	const float tileSize = 32.0f;

	InitWindow(screenWidth, screenHeight, "KibiEngine");
	SetTargetFPS(60);

	// ������������� ������ � ���������� �����������
	IsoCamera camera = {
		camera.offset = { screenWidth / 2.0f, screenHeight / 2.0f },
		camera.scale = 1.0f,
		camera.minScale = 0.5f,
		camera.maxScale = 4.0f
	};

	Texture2D tileTexture = LoadTexture("../../assets/tileset/tile_block.png");
	Vector2 mousePos = { 0 };
	Vector2 gridHover = { 0 };
	Vector2 prevMousePos = { 0 };

	while (!WindowShouldClose()) {
		prevMousePos = mousePos;
		mousePos = GetMousePosition();

		// ��������� ��������������� � ������������ Clamp
		float wheel = GetMouseWheelMove();
		if (wheel != 0) {
			Vector2 mouseWorldPos = {
				(mousePos.x - camera.offset.x) / camera.scale,
				(mousePos.y - camera.offset.y) / camera.scale
			};

			camera.scale += wheel * 0.1f;
			camera.scale = Clamp(camera.scale, camera.minScale, camera.maxScale);

			camera.offset.x = mousePos.x - mouseWorldPos.x * camera.scale;
			camera.offset.y = mousePos.y - mouseWorldPos.y * camera.scale;
		}

		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
			camera.offset.x += (mousePos.x - prevMousePos.x);
			camera.offset.y += (mousePos.y - prevMousePos.y);
		}

		Vector2 transformedMouse = {
			(mousePos.x - camera.offset.x) / camera.scale,
			(mousePos.y - camera.offset.y) / camera.scale
		};
		gridHover = ToGridCoordinate(transformedMouse, tileSize, camera.scale);
		gridHover.x = roundf(gridHover.x);
		gridHover.y = roundf(gridHover.y);

		BeginDrawing();
		ClearBackground(RAYWHITE);

		for (int y = 0; y < gridSize; y++) {
			for (int x = 0; x < gridSize; x++) {
				Vector2 screenPos = ToScreenCoordinate({ (float)x, (float)y }, tileSize, camera.scale);
				screenPos.x += camera.offset.x;
				screenPos.y += camera.offset.y;

				// ������������ ����� DrawTextureEx
				DrawTextureEx(
					tileTexture,
					Vector2 {
					screenPos.x - tileSize / 2 * camera.scale,
						screenPos.y - tileSize / 2 * camera.scale
				},
					0.0f,
					camera.scale,
					WHITE
				);
			}
		}

		if (gridHover.x >= 0 && gridHover.y >= 0 &&
			gridHover.x < gridSize && gridHover.y < gridSize) {

			Vector2 hoverPos = ToScreenCoordinate(gridHover, tileSize, camera.scale);
			hoverPos.x += camera.offset.x;
			hoverPos.y += camera.offset.y;

			// ������������ ����� DrawIsoRhombus
			DrawIsoRhombus(
				hoverPos,
				tileSize,
				camera.scale,
				RED
			);
		}

		DrawText(TextFormat("Scale: %.2f", camera.scale), 10, 10, 20, DARKGRAY);
		DrawText(TextFormat("Grid: [%d, %d]", (int)gridHover.x, (int)gridHover.y), 10, 40, 20, DARKGRAY);

		EndDrawing();
	}

	UnloadTexture(tileTexture);
	CloseWindow();
	return 0;
}

/*
#include <raylib.h>
#include <raymath.h>
#include <math.h>

struct Matrix2x2
{
	float a, b, c, d;
};

// ��������� ������
struct Camera2D
{
	Vector2 offset;
	float scale;
	float minScale;
	float maxScale;
};

// �������������� ��������� ����� � ��������
Vector2 ToScreenCoordinate(Vector2 gridPos, float tileSize, float scale)
{
	const float i_x = 1.0f;
	const float i_y = 0.5f;
	const float j_x = -1.0f;
	const float j_y = 0.5f;

	return
	{
		(gridPos.x * i_x + gridPos.y * j_x) * tileSize * 0.5f * scale,
		(gridPos.x * i_y + gridPos.y * j_y) * tileSize * 0.5f * scale
	};
}

// �������� �������������� (�������� -> �����)
Matrix2x2 InvertMatrix(float a, float b, float c, float d)
{
	float det = 1.0f / (a * d - b * c);
	return
	{
		det * d,
		det * -b,
		det * -c,
		det * a
	};
}

Vector2 ToGridCoordinate(Vector2 screenPos, float tileSize, float scale)
{
	const float a = 1.0f * 0.5f * tileSize * scale;
	const float b = -1.0f * 0.5f * tileSize * scale;
	const float c = 0.5f * 0.5f * tileSize * scale;
	const float d = 0.5f * 0.5f * tileSize * scale;

	Matrix2x2 inv = InvertMatrix(a, b, c, d);

	return
	{
		screenPos.x * inv.a + screenPos.y * inv.b,
		screenPos.x * inv.c + screenPos.y * inv.d
	};
}

// ��������� ��������������� �����
void DrawIsoRhombus(Vector2 center, float size, float scale, Color color)
{
	Vector2 points[4];

	float scaledSize = size * scale;

	points[0] = { center.x, center.y - scaledSize / 2 };
	points[1] = { center.x + scaledSize / 2, center.y };
	points[2] = { center.x, center.y + scaledSize / 2 };
	points[3] = { center.x - scaledSize / 2, center.y };

	DrawLineV(points[0], points[1], color);
	DrawLineV(points[1], points[2], color);
	DrawLineV(points[2], points[3], color);
	DrawLineV(points[3], points[0], color);
}

int main(void)
{
	const int screenWidth = 1920;
	const int screenHeight = 1080;
	const int gridSize = 20;
	const float tileSize = 32.0f;

	// �������������
	InitWindow(screenWidth, screenHeight, "KibiEngine");
	SetTargetFPS(60);

	// ������������� ������
	Camera2D camera = {
		camera.offset = { screenWidth / 2, screenHeight / 2 },
		camera.scale = 1.0f,
		camera.minScale = 0.5f,
		camera.maxScale = 4.0f
	};

	Texture2D tileTexture = LoadTexture("../../assets/tileset/tile_block.png");

	Vector2 mousePos = { 0 };
	Vector2 gridHover = { 0 };
	Vector2 prevMousePos = { 0 };

	while (!WindowShouldClose())
	{
		prevMousePos = mousePos;
		mousePos = GetMousePosition();

		// ��������� ���������������
		float wheel = GetMouseWheelMove();

		if (wheel != 0)
		{
			Vector2 mouseWorldPos = {
				(mousePos.x - camera.offset.x) / camera.scale,
				(mousePos.y - camera.offset.y) / camera.scale
			};

			camera.scale += wheel * 0.1f;
			camera.scale = Clamp(camera.scale, camera.minScale, camera.maxScale);

			camera.offset.x = mousePos.x - mouseWorldPos.x * camera.scale;
			camera.offset.y = mousePos.y - mouseWorldPos.y * camera.scale;
		}

		// ���������� ������
		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
			camera.offset.x += (mousePos.x - prevMousePos.x);
			camera.offset.y += (mousePos.y - prevMousePos.y);
		}

		// �������������� ��������� ����
		Vector2 transformedMouse = {
			(mousePos.x - camera.offset.x) / camera.scale,
			(mousePos.y - camera.offset.y) / camera.scale
		};

		gridHover = ToGridCoordinate(transformedMouse, tileSize, camera.scale);
		gridHover.x = roundf(gridHover.x);
		gridHover.y = roundf(gridHover.y);

		BeginDrawing();
		ClearBackground(RAYWHITE);

		// ��������� �����
		for (int y = 0; y < gridSize; y++)
		{
			for (int x = 0; x < gridSize; x++)
			{
				Vector2 screenPos = ToScreenCoordinate({ (float)x, (float)y }, tileSize, camera.scale);
				screenPos.x += camera.offset.x;
				screenPos.y += camera.offset.y;

				// ������ �������� � ����������������
				DrawTextureEx(
					tileTexture,
					{ screenPos.x - tileSize / 2 * camera.scale,
					  screenPos.y - tileSize / 2 * camera.scale },
					0.0f,
					camera.scale,
					WHITE
				);
			}
		}

		// ��������� ������
		if (gridHover.x >= 0 && gridHover.y >= 0 &&
			gridHover.x < gridSize && gridHover.y < gridSize) {

			Vector2 hoverPos = ToScreenCoordinate(gridHover, tileSize, camera.scale);
			hoverPos.x += camera.offset.x;
			hoverPos.y += camera.offset.y;

			// ������ �������������� ������
			DrawIsoRhombus(
				hoverPos,
				tileSize,
				camera.scale,
				RED
			);
		}

		// ���������� ����������
		DrawText(TextFormat("Scale: %.2f", camera.scale), 10, 10, 20, DARKGRAY);
		DrawText(TextFormat("Grid: [%d, %d]", (int)gridHover.x, (int)gridHover.y), 10, 40, 20, DARKGRAY);

		EndDrawing();
	}

	UnloadTexture(tileTexture);
	CloseWindow();

	return 0;
}
*/

	//Vector2 cameraOffset = {
	//	screenWidth / 2 - tileSize,
	//	screenHeight / 2 - tileSize
	//};
	//Vector2 mousePos = { 0 };
	//Vector2 gridHover = { 0 };

/*
	// ������� ����
	while (!WindowShouldClose())
	{
		// ���������� ������
		if (IsKeyDown(KEY_RIGHT)) cameraOffset.x -= 5;
		if (IsKeyDown(KEY_LEFT)) cameraOffset.x += 5;
		if (IsKeyDown(KEY_UP)) cameraOffset.y += 5;
		if (IsKeyDown(KEY_DOWN)) cameraOffset.y -= 5;

		// �������������� ��������� ����
		mousePos = GetMousePosition();
		Vector2 transformedMouse = {
			mousePos.x - cameraOffset.x,
			mousePos.y - cameraOffset.y
		};
		gridHover = ToGridCoordinate(transformedMouse, tileSize);
		gridHover.x = roundf(gridHover.x);
		gridHover.y = roundf(gridHover.y);

		BeginDrawing();
		ClearBackground(RAYWHITE);

		// ��������� �����
		for (int y = 0; y < gridSize; y++)
		{
			for (int x = 0; x < gridSize; x++)
			{
				Vector2 screenPos = ToScreenCoordinate({ (float)x, (float)y }, tileSize);
				screenPos.x += cameraOffset.x;
				screenPos.y += cameraOffset.y;

				DrawTextureEx(
					tileTexture,
					{ screenPos.x - tileSize / 2, screenPos.y - tileSize / 2 },
					0.0f,
					1.0f,
					WHITE
				);
			}
		}

		// ��������� ������ (Hover)
		if (gridHover.x >= 0 && gridHover.y >= 0 &&
			gridHover.x < gridSize && gridHover.y < gridSize) {

			Vector2 hoverPos = ToScreenCoordinate(gridHover, tileSize);
			hoverPos.x += cameraOffset.x;
			hoverPos.y += cameraOffset.y;

			DrawRectangleLines(
				hoverPos.x - tileSize / 2,
				hoverPos.y - tileSize / 2,
				tileSize,
				tileSize,
				RED
			);
		}

		EndDrawing();
	}

	// ���������������
	UnloadTexture(tileTexture);

	CloseWindow();
	return 0;
}
*/