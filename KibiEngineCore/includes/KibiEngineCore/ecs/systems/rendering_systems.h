#pragma once

#include <entt/entt.hpp>

#include <KibiEngineCore\ecs\components\transform.h>
#include <KibiEngineCore\ecs\components\renderable.h>

class RenderingSystem
{
public:
    void Update(entt::registry& registry)
    {
        auto view = registry.view<Transform, Renderable>();

        view.each([](const auto& transform, const auto& renderable)
            {
            DrawCubeTexture(
                renderable.texture,
                transform.position,
                1.0f, 1.0f, 1.0f,
                WHITE
            );
            });
    }
};