#pragma once

#include <entt\entt.hpp>

#include <raylib.h>
#include <raymath.h>

#include <KibiEngineCore\ecs\components\transform.h>
#include <KibiEngineCore\ecs\components\camera.h>

namespace KibiEngine::ECS
{
    class CameraSystem
    {
    public:
        void Update(entt::registry& registry) 
        {
            auto cameraView = registry.view<CameraComponent>();

            cameraView.each([&](auto& cameraComp)
                {
                auto focusView = registry.view<Transform, CameraFocus>();

                focusView.each([&](auto& transform, auto&)
                    {
                    cameraComp.camera.position = Vector3Add(transform.position, { 10.0f, 20.0f, 10.0f });
                    cameraComp.camera.target = transform.position;
                    cameraComp.camera.up = { 0.0f, 1.0f, 0.0f };
                    cameraComp.camera.fovy = 50.0f;
                    cameraComp.camera.projection = CAMERA_PERSPECTIVE;
                    });
                });
        }
    };
}