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

#pragma once

#include <KibiEngineCore/block.h>
#include <vector>
#include <memory>
#include <unordered_map>

namespace KibiEngine
{
    class World
    {
    public:
        World(int size, const Texture2D& texture);
        void Draw() const;
        bool HasSolidBlockAt(int x, int y, int z) const;

        // Новые методы
        void AddBlock(Vector3 position);
        void RemoveBlock(Vector3 position);
        Block* GetBlockAt(Vector3 position) const;

    private:
        std::unordered_map<std::string, std::unique_ptr<Block>> m_blocks;
        Texture2D m_blockTexture;
        int m_worldSize;

        std::string GetBlockKey(int x, int y, int z) const;
    };
}