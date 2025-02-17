#include <KibiEngineCore\world.h>
#include <memory>

namespace KibiEngine
{
    World::World(int size, Texture2D texture) : m_blockTexture(texture)
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
            }
        }
    }
}