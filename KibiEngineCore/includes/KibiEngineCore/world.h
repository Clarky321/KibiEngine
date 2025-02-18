#pragma once

#include <KibiEngineCore\block.h>
#include <vector>
#include <memory>

namespace KibiEngine
{
	class World
	{
	public:
		World(int size, Texture2D texture);
		void Draw() const;

		bool HasSolidBlockAt(int x, int y, int z) const;

	private:
		std::vector<std::vector<std::unique_ptr<Block>>> m_grid;
		Texture2D m_blockTexture;
	};
}