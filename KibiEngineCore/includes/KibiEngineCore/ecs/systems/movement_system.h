#pragma once

#include <entt\entt.hpp>

#include <raylib.h>
#include <raymath.h>

#include <KibiEngineCore\ecs\components\transform.h>
#include <KibiEngineCore\ecs\components\player_controller.h>

#include <KibiEngineCore\world.h>

namespace KibiEngine::ECS
{
    class MovementSystem
    {
    public:
        void Update(entt::registry& registry, World& world)
        {
            auto view = registry.view<Transform, PlayerController>();

            view.each([&](auto entity, Transform& transform, PlayerController& controller)
                {
                Vector3 moveDir = { 0 };

                // Обработка ввода (адаптировано из Character)
                if (IsKeyDown(KEY_W)) { moveDir.x -= 1; moveDir.z -= 1; }
                if (IsKeyDown(KEY_S)) { moveDir.x += 1; moveDir.z += 1; }
                if (IsKeyDown(KEY_A)) { moveDir.x -= 1; moveDir.z += 1; }
                if (IsKeyDown(KEY_D)) { moveDir.x += 1; moveDir.z -= 1; }

                if (Vector3Length(moveDir) > 0)
                {
                    moveDir = Vector3Normalize(moveDir);
                    Vector3 newPos = Vector3Add(transform.position, Vector3Scale(moveDir, controller.moveSpeed));

                    if (!CheckCollision(world, newPos))
                    {
                        transform.position = newPos;
                        TraceLog(LOG_INFO, "Player position: (%.2f, %.2f, %.2f)",
                            transform.position.x, transform.position.y, transform.position.z);
                    }
                }
                });
        }

    private:
        bool CheckCollision(World& world, Vector3 newPos)
        {
            Vector3 checkPoints[] = {
                newPos,
                {newPos.x, newPos.y + 1.0f, newPos.z}
            };

            for (auto& point : checkPoints)
            {
                int x = static_cast<int>(floorf(point.x));
                int z = static_cast<int>(floorf(point.z));

                if (world.HasSolidBlockAt(x, static_cast<int>(floorf(point.y)), z))
                {
                    return true;
                }
            }
            return false;
        }
    };
}