#include <raylib.h>

#include <KibiEngineCore\game.h>
#include <KibiEngineCore\resource_manager.h>
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
        InitWindow(m_screenWidth, m_screenHeight, "KibiEngine");
        SetTargetFPS(60);
        //DisableCursor();

        SetWindowState(FLAG_WINDOW_RESIZABLE);

        ResourceManager::PreloadAssets();

        const Texture2D& blockTexture = ResourceManager::LoadTexture("../../assets/tileset/dirt.png");

        m_world = std::make_unique<World>(m_worldSize, blockTexture);
        m_character = std::make_unique<Character>(Vector3{ 10.0f, 1.0f, 10.0f });
        m_cameraController = std::make_unique<CameraController>(*m_character);
    }

    void Game::Shutdown()
    {
        ResourceManager::UnloadAll();
        CloseWindow();
    }

    void Game::Run()
    {
        while (!WindowShouldClose())
        {
            m_character->Update(*m_world);
            m_cameraController->Update();

            BeginDrawing();
            ClearBackground(SKYBLUE);

            BeginMode3D(m_cameraController->GetCamera());

            m_world->Draw();
            m_character->Draw();

            EndMode3D();
            EndDrawing();
        }
    }
}