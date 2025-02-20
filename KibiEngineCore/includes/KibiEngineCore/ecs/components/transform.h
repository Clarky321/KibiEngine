#pragma once

#include <raylib.h>

namespace KibiEngine::ECS
{
	struct  Transform
	{
		Vector3 position = { 0 };
		Vector3 rotation = { 0 };
		Vector3 scale = { 1.0f, 1.0f, 1.0f };
	};
} 