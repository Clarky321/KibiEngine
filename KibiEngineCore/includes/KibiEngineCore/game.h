#pragma once

#include <memory>

#include <KibiEngineCore\world.h>
#include <KibiEngineCore\character.h>
#include <KibiEngineCore\camera_controller.h>
#include "npc_models.h"

namespace KibiEngine
{
	class Game
	{
	public:
		Game();
		void Run();

		Texture2D m_currentBlockTexture;

		bool m_showWireframe = false;

		//
		std::vector<VoxObject> m_voxObjects;
		std::unique_ptr<VoxModel> m_characterModel;
		//

	private:
		void Initialize();
		void Shutdown();

		const int m_screenWidth = 1366;
		const int m_screenHeight = 768;
		const int m_worldSize = 60;

		std::unique_ptr<World> m_world;
		//std::unique_ptr<Character> m_character;
		std::unique_ptr<CameraController> m_cameraController;
	};
}