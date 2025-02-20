#include <raylib.h>

#include <KibiEngineCore\game.h>
#include <KibiEngineCore\resource_manager.h>

namespace KibiEngine
{
    Game::Game() : world(30, ResourceManager::LoadTexture("../../assets/tileset/dirt.png"))
    {
        // Создание игрока
        auto player = world.GetRegistry().create();
        world.GetRegistry().emplace<ECS::Transform>(player, Vector3{ 10.0f, 1.0f, 10.0f });
        world.GetRegistry().emplace<ECS::PlayerController>(player);
        world.GetRegistry().emplace<ECS::Renderable>(player, &ResourceManager::LoadTexture("../../assets/tileset/orangewool.png"));

        // Настройка камеры
        auto camera = world.GetRegistry().create();
        world.GetRegistry().emplace<ECS::CameraComponent>(camera, Camera3D{ ... });
    }


    void Game::Run()
    {
        while (!WindowShouldClose())
        {
            movementSystem.Update(world.GetRegistry(), world);
            cameraSystem.Update(world.GetRegistry());

            BeginDrawing();
            ClearBackground(SKYBLUE);

            // Получаем камеру
            auto& registry = world.GetRegistry();
            auto cameraView = registry.view<ECS::CameraComponent>();
            
            cameraView.each([&](auto& cameraComp)
                {
                BeginMode3D(cameraComp.camera);
                renderingSystem.Update(registry);
                EndMode3D();
                });

            EndDrawing();
        }
    }
}

/*
    void Game::Run()
{
    while (!WindowShouldClose())
    {
        m_movementSystem.Update(m_world.GetRegistry());
        m_cameraSystem.Update(m_world.GetRegistry());

        BeginDrawing();
        ClearBackground(SKYBLUE);
        BeginMode3D(...);

        m_renderingSystem.Update(m_world.GetRegistry());

        EndMode3D();
        EndDrawing();
    }
}
*/


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
        //DisableCursor();

        // Предзагрузка всех ресурсов
        ResourceManager::PreloadAssets();

        // Получаем ссылку на текстуру через менеджер
        const Texture2D& blockTexture = ResourceManager::LoadTexture("../../assets/tileset/dirt.png");

        m_world = std::make_unique<World>(m_worldSize, blockTexture);
        m_character = std::make_unique<Character>(Vector3{ 10.0f, 1.0f, 10.0f });
        m_cameraController = std::make_unique<CameraController>(*m_character);
    }

    void Game::Shutdown()
    {
        // Удаляем все текстуры
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