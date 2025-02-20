#pragma once

#include <raylib.h>

namespace KibiEngine::ECS
{
	struct PlayerController
	{
		float moveSpeed = 0.2f;
		Vector3 velocity = { 0 };
	};
}