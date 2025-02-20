#pragma once

#include <raylib.h>

namespace KibiEngine::ECS
{
	struct CameraComponent
	{
		Camera3D camera;
	};

	struct CameraFocus {};
}