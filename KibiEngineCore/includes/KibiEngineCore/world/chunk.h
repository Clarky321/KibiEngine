#pragma once

#include <entt/entt.hpp>

#include <array>

#include <KibiEngineCore\ecs\components\transform.h>
#include <KibiEngineCore\ecs\components\renderable.h>

constexpr int CHUNK_SIZE = 16;

class Chunk {
public:
    void Generate(entt::registry& registry)
    {
        for (int x = 0; x < CHUNK_SIZE; ++x)
        {
            for (int y = 0; y < CHUNK_SIZE; ++y)
            {
                for (int z = 0; z < CHUNK_SIZE; ++z)
                {
                    auto entity = registry.create();

                    registry.emplace<Transform>(entity,
                        Vector3{ static_cast<float>(x),
                               static_cast<float>(y),
                               static_cast<float>(z) });
                    registry.emplace<Renderable>(entity, GetBlockTexture(x, y, z));
                }
            }
        }
    }

private:
    Texture2D& GetBlockTexture(int x, int y, int z)
    {
        // Логика выбора текстуры
    }
};