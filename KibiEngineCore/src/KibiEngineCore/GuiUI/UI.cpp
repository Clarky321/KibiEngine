/*
#include <raylib.h>
#include <rlImGui.h>
#include <imgui.h>
#include <imgui\styles.h>

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

    // 1. ���������� ������ �� 3 ��������� ��� RGB
    float backgroundColor[3] = {
        0.2f,  // R
        0.2f,  // G
        0.2f   // B
    };

    // 2. ���������� ��� �������������� � Color
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
        // 3. ������������ ������ � Color ����� ��������
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
        // 4. ���������� ������ � �������� �� 3 ���������
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

#include <imgui.h>
#include <rlImGui.h>
#include <style\styles.h>

#include <filesystem>
#include <iostream>

#include <KibiEngineCore\GuiUI\UI.h>
#include <KibiEngineCore\resource_manager.h>

namespace KibiEngine
{
    void UI::Initialize()
    {
        ImGuiIO& io = ImGui::GetIO();
        
        embraceTheDarkness();

        if (!io.Fonts->IsBuilt())
        {
            unsigned char* pixels;
            int width, height;
            io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);
            io.Fonts->Build();
        }

        //ImGui::StyleColorsDark();
    }

    void UI::Shutdown()
    {
        // ������� �������� ImGui
    }


    void UI::Draw(Texture2D* currentTexture, bool* showWireframe)
    {
        ImGui::Begin("TEXTURE", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

        for (const auto& [path, texture] : ResourceManager::GetTextures())
        {
            // ���������� rlImGuiImageButtonSize ��� �������� ������ � ���������
            if (rlImGuiImageButtonSize(path.c_str(), &texture, { 30, 30 }))
            {
                *currentTexture = texture;
            }

            if (ImGui::IsItemHovered())
            {
                ImGui::SetTooltip("%s", path.c_str());
            }
            ImGui::SameLine();
        }
        ImGui::End();

        ImGui::Begin("Settings");
        
        ImGui::Checkbox("Wireframe Mode", showWireframe);
        //ImGui::Checkbox("CubeWires");
        
        ImGui::End();
    }
}