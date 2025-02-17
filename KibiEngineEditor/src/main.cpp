#include <raylib.h>

int main(void)
{
	// Инициализация
	InitWindow(1200, 800, "KibiEngine");

	// Игровой цикл
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		EndDrawing();
	}

	// Деинициализация
	CloseWindow();
	return 0;
}