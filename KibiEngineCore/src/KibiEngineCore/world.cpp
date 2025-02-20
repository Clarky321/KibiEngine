#include <KibiEngineCore\world.h>

namespace KibiEngine {
    World::World(int size, const Texture2D& texture) : blockTexture(texture)
    {
        for (int x = 0; x < size; ++x)
        {
            for (int z = 0; z < size; ++z)
            {
                auto entity = registry.create();

                registry.emplace<ECS::Transform>(entity, Vector3{ (float)x, 0.0f, (float)z });
                registry.emplace<ECS::Renderable>(entity, &blockTexture);
            }
        }
    }

    bool World::HasSolidBlockAt(int x, int y, int z) const
    {
        auto view = registry.view<ECS::Transform>();

        for (auto entity : view)
        {
            auto& pos = view.get<ECS::Transform>(entity).position;

            if (static_cast<int>(pos.x) == x &&
                static_cast<int>(pos.z) == z &&
                pos.y >= y)
            {
                return true;
            }
        }
        return false;
    }
}

/*
#include <KibiEngineCore\world.h>

namespace KibiEngine
{
    World::World(int size, const Texture2D& texture)
        : m_blockTexture(texture)
    {
        for (int x = 0; x < size; ++x)
        {
            for (int z = 0; z < size; ++z)
            {
                auto entity = m_registry.create();

                m_registry.emplace<ECS::Transform>(entity, Vector3{ (float)x, 0.0f, (float)z });
                m_registry.emplace<ECS::Renderable>(entity, &m_blockTexture);
            }
        }
    }
}
*/

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

                // Рисуем рамку для отладки
                DrawCubeWires(block->GetPosition(), 1.0f, 1.0f, 1.0f, LIGHTGRAY);
            }
        }
    }

    bool World::HasSolidBlockAt(int x, int y, int z) const
    {
        if (x < 0 || x >= m_grid.size() || z < 0 || z >= m_grid[0].size())
            return true;

        // Проверяем высоту блока в конкретной ячейке
        return (m_grid[x][z]->GetPosition().y >= y);
    }
}
*/