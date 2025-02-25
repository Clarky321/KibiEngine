/*
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
*/

#include <raylib.h>

#include <KibiEngineCore\game.h>
#include <KibiEngineCore\resource_manager.h>
#include <KibiEngineCore\world.h>
#include <KibiEngineCore\camera_controller.h>
#include <raymath.h>

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

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                Ray ray = GetMouseRay(GetMousePosition(), m_cameraController->GetCamera());

                RayCollision nearestCollision = { 0 };
                for (const auto& [key, block] : m_world->GetBlocks())
                {
                    BoundingBox box = {
                        block.min = Vector3Subtract(block->GetPosition(), {0.5f, 0.5f, 0.5f}),
                        block.max = Vector3Add(block->GetPosition(), {0.5f, 0.5f, 0.5f})
                    };
            }

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