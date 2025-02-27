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
#include <cmath>

namespace KibiEngine
{

    World::World(int size, const Texture2D& texture)
        : m_blockTexture(texture), m_worldSize(size)
    {
        for (int x = 0; x < size; x++)
        {
            for (int z = 0; z < size; z++)
            {
                // Передаем текстуру явно
                AddBlock({ (float)x - size / 2.0f, 0.0f, (float)z - size / 2.0f }, m_blockTexture);
            }
        }
    }

    std::string World::GetBlockKey(int x, int y, int z) const
    {
        std::stringstream ss;
        ss << x << "," << y << "," << z;
        return ss.str();
    }

    void World::AddBlock(Vector3 position, const Texture2D& texture)
    {
        int x = static_cast<int>(std::floor(position.x));
        int y = static_cast<int>(std::floor(position.y));
        int z = static_cast<int>(std::floor(position.z));

        // Проверка границ мира (если нужно)
        if (x < 0 || x >= m_worldSize || z < 0 || z >= m_worldSize) return;

        if (!HasSolidBlockAt(x, y, z))
        {
            m_blocks[GetBlockKey(x, y, z)] = std::make_unique<Block>(
                Vector3{ (float)x, (float)y, (float)z }, texture
            );
        }
    }

    void World::RemoveBlock(Vector3 position)
    {
        int x = static_cast<int>(std::floor(position.x));
        int y = static_cast<int>(std::floor(position.y));
        int z = static_cast<int>(std::floor(position.z));

        auto key = GetBlockKey(x, y, z);
        if (m_blocks.count(key))
        {
            m_blocks.erase(key);
        }
    }

    Block* World::GetBlockAt(Vector3 position) const
    {
        int x = static_cast<int>(std::round(position.x));
        int y = static_cast<int>(std::round(position.y));
        int z = static_cast<int>(std::round(position.z));

        auto key = GetBlockKey(x, y, z);

        if (m_blocks.count(key)) return m_blocks.at(key).get();

        return nullptr;
    }

    void World::Draw(bool showWireframe) const
    {
        for (const auto& [key, block] : m_blocks)
        {
            if (!showWireframe)
            {
                block->Draw(); // Рисуем текстуру, если не включен каркас
            }
            DrawCubeWiresV(block->GetPosition(), { 1,1,1 }, WHITE); // Всегда рисуем каркас
        }
    }

    bool World::HasSolidBlockAt(int x, int y, int z) const
    {
        return m_blocks.count(GetBlockKey(x, y, z));
    }
}