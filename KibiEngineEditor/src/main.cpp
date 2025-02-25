/*
#include <raylib.h>
#include <rlImGui.h>
#include <imgui.h>
#include <style\styles.h>

int main()
{
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Raylib + ImGui Demo");

    rlImGuiSetup(true);

    embraceTheDarkness();

    int boxPositionY = screenHeight / 2 - 40;
    int scrollSpeed = 4;
    float circleRadius = 50.0f;

    SetTargetFPS(60);

    // 1. Используем массив из 3 элементов для RGB
    float backgroundColor[3] = {
        0.2f,  // R
        0.2f,  // G
        0.2f   // B
    };

    // 2. Переменная для преобразования в Color
    Color rayColor = ColorFromNormalized({
        backgroundColor[0],
        backgroundColor[1],
        backgroundColor[2],
        1.0f  // Alpha
        });

    while (!WindowShouldClose())
    {
        boxPositionY -= (int)(GetMouseWheelMove() * scrollSpeed);

        BeginDrawing();
        // 3. Конвертируем массив в Color перед очисткой
        rayColor = ColorFromNormalized({
            backgroundColor[0],
            backgroundColor[1],
            backgroundColor[2],
            1.0f
            });
        ClearBackground(rayColor);
        DrawText("Hello Raylib!", 10, 10, 20, LIGHTGRAY);

        DrawRectangle(screenWidth / 2 - 40, boxPositionY, 80, 80, MAROON);

        DrawText("Use mouse wheel to move the cube up and down!", 10, 10, 20, GRAY);
        DrawText(TextFormat("Box position Y: %03i", boxPositionY), 10, 40, 20, LIGHTGRAY);

        rlImGuiBegin();

        ImGui::Begin("Control Panel");
        // 4. Безопасная работа с массивом из 3 элементов
        ImGui::ColorEdit3("Background", backgroundColor);
        ImGui::End();
        rlImGuiEnd();

        EndDrawing();
    }

    rlImGuiShutdown();
    CloseWindow();
    return 0;
}
*/



#include <KibiEngineCore\game.h>

int main()
{
	KibiEngine::Game game;
	game.Run();

	return 0;
}