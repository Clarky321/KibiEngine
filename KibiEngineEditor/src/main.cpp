#include <raylib.h>

int main(void)
{
	// �������������
	InitWindow(1200, 800, "KibiEngine");

	// ������� ����
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		EndDrawing();
	}

	// ���������������
	CloseWindow();
	return 0;
}