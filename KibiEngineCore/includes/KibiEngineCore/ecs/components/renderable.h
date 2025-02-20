#pragma once

#include <raylib.h>

namespace KibiEngine::ECS
{
	struct Renderable
	{
		const Texture2D& texture;
		Color color = WHITE;
	};
}