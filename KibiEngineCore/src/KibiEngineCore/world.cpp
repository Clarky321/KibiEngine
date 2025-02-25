/*
#include <memory>

#include <KibiEngineCore\world.h>

namespace KibiEngine
{
    World::World(int size, const Texture2D& texture) : m_blockTexture(texture)
    {
        m_grid.resize(size);

        for (int x = 0; x < size; ++x)
        {
            m_grid[x].reserve(size);

            for (int z = 0; z < size; ++z)
            {
                m_grid[x].emplace_back(std::make_unique<Block>(
                    Vector3{ (float)x, 0.0f, (float)z }, m_blockTexture
                ));
            }
        }
    }

    void World::Draw() const
    {
        for (const auto& row : m_grid)
        {
            for (const auto& block : row)
            {
                block->Draw();

                DrawCubeWires(block->GetPosition(), 1.0f, 1.0f, 1.0f, LIGHTGRAY);
            }
        }
    }

    bool World::HasSolidBlockAt(int x, int y, int z) const
    {
        if (x < 0 || x >= m_grid.size() || z < 0 || z >= m_grid[0].size())
            return true;

        return (m_grid[x][z]->GetPosition().y >= y);
    }
}
*/

#include <KibiEngineCore/world.h>
#include <sstream>

namespace KibiEngine {
    std::string World::GetBlockKey(int x, int y, int z) const {
        std::stringstream ss;
        ss << x << "," << y << "," << z;
        return ss.str();
    }

    void World::AddBlock(Vector3 position) {
        int x = static_cast<int>(roundf(position.x));
        int y = static_cast<int>(roundf(position.y));
        int z = static_cast<int>(roundf(position.z));

        if (!HasSolidBlockAt(x, y, z)) {
            m_blocks[GetBlockKey(x, y, z)] = std::make_unique<Block>(
                Vector3{ (float)x, (float)y, (float)z }, m_blockTexture
            );
        }
    }

    void World::RemoveBlock(Vector3 position) {
        int x = static_cast<int>(roundf(position.x));
        int y = static_cast<int>(roundf(position.y));
        int z = static_cast<int>(roundf(position.z));

        auto key = GetBlockKey(x, y, z);
        if (m_blocks.count(key)) {
            m_blocks.erase(key);
        }
    }

    Block* World::GetBlockAt(Vector3 position) const {
        int x = static_cast<int>(roundf(position.x));
        int y = static_cast<int>(roundf(position.y));
        int z = static_cast<int>(roundf(position.z));

        auto key = GetBlockKey(x, y, z);
        if (m_blocks.count(key)) return m_blocks.at(key).get();
        return nullptr;
    }

    void World::Draw() const
    {
        for (const auto& [key, block] : m_blocks)
        {
            block->Draw();
            DrawCubeWiresV(block->GetPosition(), { 1,1,1 }, LIGHTGRAY);
        }
    }

    bool World::HasSolidBlockAt(int x, int y, int z) const
    {
        return m_blocks.count(GetBlockKey(x, y, z));
    }
}