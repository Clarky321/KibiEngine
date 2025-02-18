/*
#pragma once

#include <raylib.h>

namespace KibiEngine
{
	class CameraController
	{
	public:
		CameraController(Vector3 position, float speed, float sensitivity);
		Camera3D GetCamera() const;
		void Update();

	private:
		Camera3D m_camera;
		float m_movementSpeed;
		float m_mouseSensitivity;
	};
}
*/

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