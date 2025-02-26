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
#include <raymath.h>

#include <KibiEngineCore\game.h>
#include <KibiEngineCore\resource_manager.h>
#include <KibiEngineCore\world.h>
#include <KibiEngineCore\camera_controller.h>
#include <KibiEngineCore\GuiUI\UI.h>

#include <rlImGui.h>

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
        
        m_currentBlockTexture = ResourceManager::LoadTexture("../../assets/tileset/wood.png");

        m_world = std::make_unique<World>(m_worldSize, m_currentBlockTexture);

        m_cameraController = std::make_unique<CameraController>(m_worldSize);

        rlImGuiSetup(true);

        UI::Initialize();
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
            m_cameraController->Update();

            Ray ray = GetMouseRay(GetMousePosition(), m_cameraController->GetCamera());
            RayCollision nearestCollision = { nearestCollision.hit = false };

            // Поиск ближайшего блока
            for (const auto& [key, block] : m_world->GetBlocks())
            {
                BoundingBox box = {
                    box.min = Vector3Subtract(block->GetPosition(), {0.5f, 0.5f, 0.5f}),
                    box.max = Vector3Add(block->GetPosition(), {0.5f, 0.5f, 0.5f})
                };

                RayCollision collision = GetRayCollisionBox(ray, box);
                if (collision.hit && (!nearestCollision.hit || collision.distance < nearestCollision.distance))
                {
                    nearestCollision = collision;
                }
            }

            // Добавление блока (ЛКМ)
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && nearestCollision.hit)
            {

                Vector3 newPos = Vector3Add(nearestCollision.point,
                    Vector3Scale(nearestCollision.normal, 0.5f));
                m_world->AddBlock(newPos, m_currentBlockTexture);
            }

            // Удаление блока (ПКМ)
            if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON) && nearestCollision.hit)
            {
                m_world->RemoveBlock(nearestCollision.point);
            }

            // Отрисовка
            BeginDrawing();
            ClearBackground(SKYBLUE);

            BeginMode3D(m_cameraController->GetCamera());
            m_world->Draw(m_showWireframe);

            // Подсветка выбранного блока
            if (nearestCollision.hit)
            {
                DrawCubeWiresV(
                    Vector3Add(nearestCollision.point, nearestCollision.normal),
                    { 0.9f, 0.9f, 0.9f },
                    RED
                );
            }

            EndMode3D();

            rlImGuiBegin();
            UI::Draw(&m_currentBlockTexture, &m_showWireframe);
            rlImGuiEnd();

            EndDrawing();
        }
    }
}