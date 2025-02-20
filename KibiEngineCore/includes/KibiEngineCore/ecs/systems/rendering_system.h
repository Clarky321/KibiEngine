#pragma once

#include <entt\entt.hpp>

#include <KibiEngineCore\ecs\components\transform.h>
#include <KibiEngineCore\ecs\components\renderable.h>

#include <KibiEngineCore\graphics_utils.h>

namespace KibiEngine::ECS
{
    class RenderingSystem
    {
    public:
        void Update(entt::registry& registry)
        {
            auto view = registry.view<Transform, Renderable>();

            view.each([&](auto& transform, auto& renderable)
                {
                Graphics::DrawCubeTexture(*renderable.texture, ...);
                });
        }
    };
}