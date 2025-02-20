#pragma once

#include <entt\entt.hpp>

#include <KibiEngineCore\ecs\components\transform.h>
#include <KibiEngineCore\ecs\components\renderable.h>

namespace KibiEngine
{
	class World
	{
	public:
		World(int size, const Texture2D& texture);

		bool HasSolidBlockAt(int x, int y, int z) const;
		entt::registry& GetRegistry() { return registry; }

	private:
		entt::registry registry;
		const Texture2D& blockTexture;
	};
}

/*
#pragma once

#include <KibiEngineCore\block.h>
#include <vector>
#include <memory>

namespace KibiEngine
{
	class World
	{
	public:
		World(int size, const Texture2D& texture);
		void Draw() const;

		bool HasSolidBlockAt(int x, int y, int z) const;

	private:
		std::vector<std::vector<std::unique_ptr<Block>>> m_grid;
		Texture2D m_blockTexture;
	};
}
*/