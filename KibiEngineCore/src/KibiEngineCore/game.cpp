#include <raylib.h>

#include <KibiEngineCore\game.h>

#include <KibiEngineCore\world.h>
#include <KibiEngineCore\camera_controller.h>

namespace KibiEngine
{
    Game::Game()
    {
        Initialize();
    }

    void Game::Initialize()
    {
        InitWindow(m_screenWidth, m_screenHeight, "KibiEngine Demo");
        SetTargetFPS(60);
        
        DisableCursor();

        m_blockTexture = LoadTexture("../../assets/tileset/dirt.png");

        m_world = std::make_unique<World>(m_worldSize, m_blockTexture);
        m_cameraController = std::make_unique<CameraController>(
            Vector3{ 10.0f, 2.0f, 10.0f }, 0.1f, 0.005f
        );
    }

    void Game::Shutdown()
    {
        UnloadTexture(m_blockTexture);
        CloseWindow();
    }

    void Game::Run()
    {
        while (!WindowShouldClose())
        {
            m_cameraController->Update();

            BeginDrawing();

            ClearBackground(SKYBLUE);

            BeginMode3D(m_cameraController->GetCamera());

            m_world->Draw();

            EndMode3D();

            EndDrawing();
        }
    }
}