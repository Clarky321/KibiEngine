#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>
#include <vector>

void DrawCubeTexture(Texture2D texture, Vector3 position, float width, float height, float length, Color color);
void DrawCubeTextureRec(Texture2D texture, Rectangle source, Vector3 position, float width, float height, float length, Color color);

class Block {
private:
	Vector3 position;
	Texture2D texture;

public:
	// Конструктор по умолчанию (например, создаёт блок в позиции (0,0,0) с "пустой" текстурой)
	Block() : position({ 0.0f, 0.0f, 0.0f }) {
		// Можно инициализировать texture значением по умолчанию, если это имеет смысл
		texture.id = 0;
		texture.width = texture.height = 0;
		texture.mipmaps = 0;
		texture.format = 0;
	}

	Block(Vector3 pos, Texture2D tex) : position(pos), texture(tex) {}

	void Draw() const {
		DrawCubeTexture(texture, position, 1.0f, 1.0f, 1.0f, WHITE);
	}
};

class World {
private:
	std::vector<std::vector<Block>> grid;
	Texture2D blockTexture;

public:
	World(int size, Texture2D tex) : blockTexture(tex) {
		for (int x = 0; x < size; x++) {
			std::vector<Block> row;
			for (int z = 0; z < size; z++) {
				row.push_back(Block({ (float)x, 0.0f, (float)z }, blockTexture));
			}
			grid.push_back(row);
		}
	}

	void Draw() const {
		for (const auto& row : grid) {
			for (const auto& block : row) {
				block.Draw();
			}
		}
	}
};

class CameraController {
private:
	Camera3D camera;
	float movementSpeed;
	float mouseSensitivity;

public:
	CameraController(Vector3 position, float speed, float sensitivity)
		: movementSpeed(speed), mouseSensitivity(sensitivity) {
		camera.position = position;
		camera.target = { 0.0f, 0.0f, 0.0f };
		camera.up = { 0.0f, 1.0f, 0.0f };
		camera.fovy = 60.0f;
		camera.projection = CAMERA_PERSPECTIVE;
	}

	Camera3D GetCamera() const { return camera; }

	void Update() {
		// Вращение камеры мышью
		Vector2 mouseDelta = GetMouseDelta();
		camera.target.x += mouseDelta.x * mouseSensitivity;
		camera.target.y -= mouseDelta.y * mouseSensitivity;

		// Движение камеры
		Vector3 forward = Vector3Normalize(Vector3Subtract(camera.target, camera.position));
		Vector3 right = Vector3CrossProduct(forward, { 0.0f, 1.0f, 0.0f });

		if (IsKeyDown(KEY_W)) camera.position = Vector3Add(camera.position, Vector3Scale(forward, movementSpeed));
		if (IsKeyDown(KEY_S)) camera.position = Vector3Subtract(camera.position, Vector3Scale(forward, movementSpeed));
		if (IsKeyDown(KEY_A)) camera.position = Vector3Subtract(camera.position, Vector3Scale(right, movementSpeed));
		if (IsKeyDown(KEY_D)) camera.position = Vector3Add(camera.position, Vector3Scale(right, movementSpeed));

		// Обновление цели камеры для плавного движения
		camera.target = Vector3Add(camera.position, forward);
	}
};

class Game {
private:
	const int screenWidth = 1280;
	const int screenHeight = 720;
	const int worldSize = 20;

	World* world;
	CameraController* cameraController;
	Texture2D blockTexture;

public:
	Game() {
		InitWindow(screenWidth, screenHeight, "My Game Engine");
		SetTargetFPS(60);
		DisableCursor();

		blockTexture = LoadTexture("../../assets/tileset/dirt.png"); // Замените на путь к вашей текстуре
		world = new World(worldSize, blockTexture);
		cameraController = new CameraController({ 10.0f, 2.0f, 10.0f }, 0.1f, 0.005f);
	}

	~Game() {
		UnloadTexture(blockTexture);
		delete world;
		delete cameraController;
		CloseWindow();
	}

	void Run() {
		while (!WindowShouldClose()) {
			cameraController->Update();

			BeginDrawing();
			ClearBackground(SKYBLUE);
			BeginMode3D(cameraController->GetCamera());
			world->Draw();
			EndMode3D();
			EndDrawing();
		}
	}
};

int main() {
	Game game;
	game.Run();
	return 0;
}

void DrawCubeTexture(Texture2D texture, Vector3 position, float width, float height, float length, Color color)
{
	float x = position.x;
	float y = position.y;
	float z = position.z;

	// Set desired texture to be enabled while drawing following vertex data
	rlSetTexture(texture.id);

	// Vertex data transformation can be defined with the commented lines,
	// but in this example we calculate the transformed vertex data directly when calling rlVertex3f()
	//rlPushMatrix();
		// NOTE: Transformation is applied in inverse order (scale -> rotate -> translate)
		//rlTranslatef(2.0f, 0.0f, 0.0f);
		//rlRotatef(45, 0, 1, 0);
		//rlScalef(2.0f, 2.0f, 2.0f);

	rlBegin(RL_QUADS);
	rlColor4ub(color.r, color.g, color.b, color.a);
	// Front Face
	rlNormal3f(0.0f, 0.0f, 1.0f);       // Normal Pointing Towards Viewer
	rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x - width / 2, y - height / 2, z + length / 2);  // Bottom Left Of The Texture and Quad
	rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x + width / 2, y - height / 2, z + length / 2);  // Bottom Right Of The Texture and Quad
	rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x + width / 2, y + height / 2, z + length / 2);  // Top Right Of The Texture and Quad
	rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x - width / 2, y + height / 2, z + length / 2);  // Top Left Of The Texture and Quad
	// Back Face
	rlNormal3f(0.0f, 0.0f, -1.0f);     // Normal Pointing Away From Viewer
	rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x - width / 2, y - height / 2, z - length / 2);  // Bottom Right Of The Texture and Quad
	rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x - width / 2, y + height / 2, z - length / 2);  // Top Right Of The Texture and Quad
	rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x + width / 2, y + height / 2, z - length / 2);  // Top Left Of The Texture and Quad
	rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x + width / 2, y - height / 2, z - length / 2);  // Bottom Left Of The Texture and Quad
	// Top Face
	rlNormal3f(0.0f, 1.0f, 0.0f);       // Normal Pointing Up
	rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x - width / 2, y + height / 2, z - length / 2);  // Top Left Of The Texture and Quad
	rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x - width / 2, y + height / 2, z + length / 2);  // Bottom Left Of The Texture and Quad
	rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x + width / 2, y + height / 2, z + length / 2);  // Bottom Right Of The Texture and Quad
	rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x + width / 2, y + height / 2, z - length / 2);  // Top Right Of The Texture and Quad
	// Bottom Face
	rlNormal3f(0.0f, -1.0f, 0.0f);     // Normal Pointing Down
	rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x - width / 2, y - height / 2, z - length / 2);  // Top Right Of The Texture and Quad
	rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x + width / 2, y - height / 2, z - length / 2);  // Top Left Of The Texture and Quad
	rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x + width / 2, y - height / 2, z + length / 2);  // Bottom Left Of The Texture and Quad
	rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x - width / 2, y - height / 2, z + length / 2);  // Bottom Right Of The Texture and Quad
	// Right face
	rlNormal3f(1.0f, 0.0f, 0.0f);       // Normal Pointing Right
	rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x + width / 2, y - height / 2, z - length / 2);  // Bottom Right Of The Texture and Quad
	rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x + width / 2, y + height / 2, z - length / 2);  // Top Right Of The Texture and Quad
	rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x + width / 2, y + height / 2, z + length / 2);  // Top Left Of The Texture and Quad
	rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x + width / 2, y - height / 2, z + length / 2);  // Bottom Left Of The Texture and Quad
	// Left Face
	rlNormal3f(-1.0f, 0.0f, 0.0f);    // Normal Pointing Left
	rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x - width / 2, y - height / 2, z - length / 2);  // Bottom Left Of The Texture and Quad
	rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x - width / 2, y - height / 2, z + length / 2);  // Bottom Right Of The Texture and Quad
	rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x - width / 2, y + height / 2, z + length / 2);  // Top Right Of The Texture and Quad
	rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x - width / 2, y + height / 2, z - length / 2);  // Top Left Of The Texture and Quad
	rlEnd();
	//rlPopMatrix();

	rlSetTexture(0);
}

// Draw cube with texture piece applied to all faces
void DrawCubeTextureRec(Texture2D texture, Rectangle source, Vector3 position, float width, float height, float length, Color color)
{
	float x = position.x;
	float y = position.y;
	float z = position.z;
	float texWidth = (float)texture.width;
	float texHeight = (float)texture.height;

	// Set desired texture to be enabled while drawing following vertex data
	rlSetTexture(texture.id);

	// We calculate the normalized texture coordinates for the desired texture-source-rectangle
	// It means converting from (tex.width, tex.height) coordinates to [0.0f, 1.0f] equivalent 
	rlBegin(RL_QUADS);
	rlColor4ub(color.r, color.g, color.b, color.a);

	// Front face
	rlNormal3f(0.0f, 0.0f, 1.0f);
	rlTexCoord2f(source.x / texWidth, (source.y + source.height) / texHeight);
	rlVertex3f(x - width / 2, y - height / 2, z + length / 2);
	rlTexCoord2f((source.x + source.width) / texWidth, (source.y + source.height) / texHeight);
	rlVertex3f(x + width / 2, y - height / 2, z + length / 2);
	rlTexCoord2f((source.x + source.width) / texWidth, source.y / texHeight);
	rlVertex3f(x + width / 2, y + height / 2, z + length / 2);
	rlTexCoord2f(source.x / texWidth, source.y / texHeight);
	rlVertex3f(x - width / 2, y + height / 2, z + length / 2);

	// Back face
	rlNormal3f(0.0f, 0.0f, -1.0f);
	rlTexCoord2f((source.x + source.width) / texWidth, (source.y + source.height) / texHeight);
	rlVertex3f(x - width / 2, y - height / 2, z - length / 2);
	rlTexCoord2f((source.x + source.width) / texWidth, source.y / texHeight);
	rlVertex3f(x - width / 2, y + height / 2, z - length / 2);
	rlTexCoord2f(source.x / texWidth, source.y / texHeight);
	rlVertex3f(x + width / 2, y + height / 2, z - length / 2);
	rlTexCoord2f(source.x / texWidth, (source.y + source.height) / texHeight);
	rlVertex3f(x + width / 2, y - height / 2, z - length / 2);

	// Top face
	rlNormal3f(0.0f, 1.0f, 0.0f);
	rlTexCoord2f(source.x / texWidth, source.y / texHeight);
	rlVertex3f(x - width / 2, y + height / 2, z - length / 2);
	rlTexCoord2f(source.x / texWidth, (source.y + source.height) / texHeight);
	rlVertex3f(x - width / 2, y + height / 2, z + length / 2);
	rlTexCoord2f((source.x + source.width) / texWidth, (source.y + source.height) / texHeight);
	rlVertex3f(x + width / 2, y + height / 2, z + length / 2);
	rlTexCoord2f((source.x + source.width) / texWidth, source.y / texHeight);
	rlVertex3f(x + width / 2, y + height / 2, z - length / 2);

	// Bottom face
	rlNormal3f(0.0f, -1.0f, 0.0f);
	rlTexCoord2f((source.x + source.width) / texWidth, source.y / texHeight);
	rlVertex3f(x - width / 2, y - height / 2, z - length / 2);
	rlTexCoord2f(source.x / texWidth, source.y / texHeight);
	rlVertex3f(x + width / 2, y - height / 2, z - length / 2);
	rlTexCoord2f(source.x / texWidth, (source.y + source.height) / texHeight);
	rlVertex3f(x + width / 2, y - height / 2, z + length / 2);
	rlTexCoord2f((source.x + source.width) / texWidth, (source.y + source.height) / texHeight);
	rlVertex3f(x - width / 2, y - height / 2, z + length / 2);

	// Right face
	rlNormal3f(1.0f, 0.0f, 0.0f);
	rlTexCoord2f((source.x + source.width) / texWidth, (source.y + source.height) / texHeight);
	rlVertex3f(x + width / 2, y - height / 2, z - length / 2);
	rlTexCoord2f((source.x + source.width) / texWidth, source.y / texHeight);
	rlVertex3f(x + width / 2, y + height / 2, z - length / 2);
	rlTexCoord2f(source.x / texWidth, source.y / texHeight);
	rlVertex3f(x + width / 2, y + height / 2, z + length / 2);
	rlTexCoord2f(source.x / texWidth, (source.y + source.height) / texHeight);
	rlVertex3f(x + width / 2, y - height / 2, z + length / 2);

	// Left face
	rlNormal3f(-1.0f, 0.0f, 0.0f);
	rlTexCoord2f(source.x / texWidth, (source.y + source.height) / texHeight);
	rlVertex3f(x - width / 2, y - height / 2, z - length / 2);
	rlTexCoord2f((source.x + source.width) / texWidth, (source.y + source.height) / texHeight);
	rlVertex3f(x - width / 2, y - height / 2, z + length / 2);
	rlTexCoord2f((source.x + source.width) / texWidth, source.y / texHeight);
	rlVertex3f(x - width / 2, y + height / 2, z + length / 2);
	rlTexCoord2f(source.x / texWidth, source.y / texHeight);
	rlVertex3f(x - width / 2, y + height / 2, z - length / 2);

	rlEnd();

	rlSetTexture(0);
}

/*
#include "raylib.h"
#include <vector>

// Класс, представляющий отдельный блок (куб)
class Block {
public:
	Vector3 position; // Центр куба
	float size;       // Размер куба (по всем осям)

	Block(Vector3 pos, float s) : position(pos), size(s) {}

	// Метод для отрисовки блока с наложенной текстурой
	void Draw(Texture2D texture) {
		// Отрисовка куба с текстурой (одинаковая текстура на всех гранях)
		//DrawCubeTexture(texture, position, size, size, size, WHITE);
		//DrawCube(position, float width, height, length, Color color);
		// Отрисовка каркаса куба для визуального выделения его границ
		DrawCubeWires(position, size, size, size, BLACK);
	}
};

// Класс, представляющий сетку блоков (например, 20x20)
class Grid {
public:
	std::vector<Block> blocks;
	int gridSize;    // Количество блоков по одной стороне сетки
	float blockSize; // Размер одного блока

	Grid(int gridSize, float blockSize) : gridSize(gridSize), blockSize(blockSize) {
		// Вычисляем смещение для центрирования сетки относительно начала координат
		float offset = (gridSize * blockSize) / 2.0f;
		// Заполняем вектор блоками, располагая их на плоскости XZ
		for (int x = 0; x < gridSize; x++) {
			for (int z = 0; z < gridSize; z++) {
				Vector3 pos;
				// Расположение таково, что центр каждого блока сдвинут на half-size
				pos.x = x * blockSize - offset + blockSize / 2.0f;
				pos.y = blockSize / 2.0f; // чтобы нижняя грань касалась Y=0
				pos.z = z * blockSize - offset + blockSize / 2.0f;
				blocks.push_back(Block(pos, blockSize));
			}
		}
	}

	// Метод для отрисовки всех блоков в сетке
	void Draw(Texture2D texture) {
		for (auto& block : blocks) {
			block.Draw(texture);
		}
	}
};

int main() {
	// Инициализация окна
	const int screenWidth = 1920;
	const int screenHeight = 1280;
	InitWindow(screenWidth, screenHeight, "Простой игровой движок на raylib");

	// Загрузка текстуры для блока (убедитесь, что файл block.png находится в папке resources)
	Texture2D blockTexture = LoadTexture("resources/block.png");

	// Создаем сетку блоков 20x20, где каждый блок имеет размер 2.0f
	const int gridSize = 20;
	const float blockSize = 2.0f;
	Grid grid(gridSize, blockSize);

	// Настройка камеры от первого лица
	Camera camera = { 0 };
	camera.position = { 0.0f, 10.0f, 20.0f };   // Начальная позиция камеры
	camera.target = { 0.0f, 0.0f,  0.0f };      // Точка, на которую направлена камера
	camera.up = { 0.0f, 1.0f,  0.0f };      // Направление "вверх"
	camera.fovy = 60.0f;                       // Угол обзора
	camera.projection = CAMERA_PERSPECTIVE;

	// Устанавливаем режим камеры от первого лица
	//SetCameraMode(camera, CAMERA_FIRST_PERSON);
	// Скрываем курсор для управления мышью
	DisableCursor();

	SetTargetFPS(60);

	// Главный игровой цикл
	while (!WindowShouldClose()) {
		// Обновление камеры (обработка перемещения и поворота мышью)
		UpdateCamera(&camera, CAMERA_FIRST_PERSON);

		BeginDrawing();
		ClearBackground(RAYWHITE);

		BeginMode3D(camera);
		// Отрисовка сетки блоков с наложенной текстурой
		grid.Draw(blockTexture);
		EndMode3D();

		// Отрисовка информации на экране
		DrawText("Управление: WASD для перемещения, мышь для поворота", 10, 10, 20, DARKGRAY);
		EndDrawing();
	}

	// Очистка ресурсов
	UnloadTexture(blockTexture);
	CloseWindow();

	return 0;
}
*/

/*
#include <raylib.h>
#include <raymath.h>

struct Matrix2x2 {
	float a, b, c, d;
};

// Переименованная структура камеры
struct IsoCamera {
	Vector2 offset;
	float scale;
	float minScale;
	float maxScale;
};

// Обновлённая функция преобразования координат
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

// Обновлённая функция рисования ромба
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

	// Инициализация камеры с правильным синтаксисом
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

		// Обработка масштабирования с исправленным Clamp
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

				// Исправленный вызов DrawTextureEx
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

			// Исправленный вызов DrawIsoRhombus
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
*/

/*
#include <raylib.h>
#include <raymath.h>
#include <math.h>

struct Matrix2x2
{
	float a, b, c, d;
};

// Параметры камеры
struct Camera2D
{
	Vector2 offset;
	float scale;
	float minScale;
	float maxScale;
};

// Преобразование координат сетки в экранные
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

// Обратное преобразование (экранные -> сетка)
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

// Рисование изометрического ромба
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

	// Инициализация
	InitWindow(screenWidth, screenHeight, "KibiEngine");
	SetTargetFPS(60);

	// Инициализация камеры
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

		// Обработка масштабирования
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

		// Обновление камеры
		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
			camera.offset.x += (mousePos.x - prevMousePos.x);
			camera.offset.y += (mousePos.y - prevMousePos.y);
		}

		// Преобразование координат мыши
		Vector2 transformedMouse = {
			(mousePos.x - camera.offset.x) / camera.scale,
			(mousePos.y - camera.offset.y) / camera.scale
		};

		gridHover = ToGridCoordinate(transformedMouse, tileSize, camera.scale);
		gridHover.x = roundf(gridHover.x);
		gridHover.y = roundf(gridHover.y);

		BeginDrawing();
		ClearBackground(RAYWHITE);

		// Отрисовка сетки
		for (int y = 0; y < gridSize; y++)
		{
			for (int x = 0; x < gridSize; x++)
			{
				Vector2 screenPos = ToScreenCoordinate({ (float)x, (float)y }, tileSize, camera.scale);
				screenPos.x += camera.offset.x;
				screenPos.y += camera.offset.y;

				// Рисуем текстуру с масштабированием
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

		// Отрисовка ховера
		if (gridHover.x >= 0 && gridHover.y >= 0 &&
			gridHover.x < gridSize && gridHover.y < gridSize) {

			Vector2 hoverPos = ToScreenCoordinate(gridHover, tileSize, camera.scale);
			hoverPos.x += camera.offset.x;
			hoverPos.y += camera.offset.y;

			// Рисуем изометрический контур
			DrawIsoRhombus(
				hoverPos,
				tileSize,
				camera.scale,
				RED
			);
		}

		// Отладочная информация
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
	// Игровой цикл
	while (!WindowShouldClose())
	{
		// Обновление камеры
		if (IsKeyDown(KEY_RIGHT)) cameraOffset.x -= 5;
		if (IsKeyDown(KEY_LEFT)) cameraOffset.x += 5;
		if (IsKeyDown(KEY_UP)) cameraOffset.y += 5;
		if (IsKeyDown(KEY_DOWN)) cameraOffset.y -= 5;

		// Преобразование координат мыши
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

		// Отрисовка сетки
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

		// Отрисовка ховера (Hover)
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

	// Деинициализация
	UnloadTexture(tileTexture);

	CloseWindow();
	return 0;
}
*/