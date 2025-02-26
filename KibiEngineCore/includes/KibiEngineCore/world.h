#pragma once

#include <vector>
#include <memory>
#include <unordered_map>
#include <string>

#include <KibiEngineCore/block.h>

namespace KibiEngine
{
    class World
    {
    public:
        World(int size, const Texture2D& texture);
        void Draw(bool showWireframe) const;
        bool HasSolidBlockAt(int x, int y, int z) const;

        void AddBlock(Vector3 position, const Texture2D& texture);
        void RemoveBlock(Vector3 position);
        Block* GetBlockAt(Vector3 position) const;

        const std::unordered_map<std::string, std::unique_ptr<Block>>& GetBlocks() const { return m_blocks; }

    private:
        std::unordered_map<std::string, std::unique_ptr<Block>> m_blocks;
        Texture2D m_blockTexture;
        int m_worldSize;

        std::string GetBlockKey(int x, int y, int z) const;
    };
}