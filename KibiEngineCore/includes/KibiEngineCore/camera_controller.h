#pragma once

#include <raylib.h>
#include <KibiEngineCore\character.h>

namespace KibiEngine {
	class CameraController
	{
	public:
		CameraController(const Character& character);
		Camera3D GetCamera() const;
		void Update();

	private:
		const Character& m_character;
		Camera3D m_camera;

		void UpdateIsometricView();
	};
}