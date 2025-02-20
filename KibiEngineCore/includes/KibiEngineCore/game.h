#pragma once

#include <entt\entt.hpp>

#include <KibiEngineCore\world.h>

#include <KibiEngineCore\ecs\systems\movement_system.h>
#include <KibiEngineCore\ecs\systems\rendering_system.h>
#include <KibiEngineCore\ecs\systems\camera_system.h>

namespace KibiEngine
{
	class Game
	{
	public:
		Game();
		void Run();

	private:
		World world;

		ECS::MovementSystem movementSystem;
		ECS::RenderingSystem renderingSystem;
		ECS::CameraSystem cameraSystem;
	};
}

/*
#pragma once

#include <memory>

#include <KibiEngineCore\world.h>
#include <KibiEngineCore\character.h>
#include <KibiEngineCore\camera_controller.h>

namespace KibiEngine
{
	class Game
	{
	public:
		Game();
		void Run();

	private:
		void Initialize();
		void Shutdown();

		const int m_screenWidth = 1366;
		const int m_screenHeight = 768;
		const int m_worldSize = 30;

		std::unique_ptr<World> m_world;
		std::unique_ptr<Character> m_character;
		std::unique_ptr<CameraController> m_cameraController;
	};
}
*/