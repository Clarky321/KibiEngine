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

		const int m_screenWidth = 1920;
		const int m_screenHeight = 1200;
		const int m_worldSize = 30;

		std::unique_ptr<World> m_world;
		std::unique_ptr<Character> m_character;
		std::unique_ptr<CameraController> m_cameraController;
	};
}