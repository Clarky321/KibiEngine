#include <KibiEngineCore\character.h>
#include <raymath.h>

namespace KibiEngine
{
    Character::Character(Vector3 position) :
        m_position(position),
        m_textureLower(&ResourceManager::LoadTexture("../../assets/tileset/orangewool.png")),
        m_textureUpper(&ResourceManager::LoadTexture("../../assets/tileset/woolcoloredblue.png"))
    {
        UpdateBlocksPosition();
    }

    Character::~Character()
    {
        // –есурсы управл€ютс€ ResourceManager
    }

    void Character::Update(World& world)
    {
        Vector3 moveDir = { 0 };

        if (IsKeyDown(KEY_W)) { moveDir.x -= 1; moveDir.z -= 1; }
        if (IsKeyDown(KEY_S)) { moveDir.x += 1; moveDir.z += 1; }
        if (IsKeyDown(KEY_A)) { moveDir.x -= 1; moveDir.z += 1; }
        if (IsKeyDown(KEY_D)) { moveDir.x += 1; moveDir.z -= 1; }

        if (Vector3Length(moveDir) > 0)
        {
            moveDir = Vector3Normalize(moveDir);
            Vector3 newPos = Vector3Add(m_position, Vector3Scale(moveDir, m_moveSpeed));

            if (!CheckCollision(world, newPos))
            {
                m_position = newPos;
                UpdateBlocksPosition();
            }

            TraceLog
            (
                LOG_INFO, "Player position: (%.2f, %.2f, %.2f)",
                m_position.x, m_position.y, m_position.z
            );
        }
    }

    void Character::UpdateBlocksPosition()
    {
        m_lowerBlock = Block(m_position, *m_textureLower);
        m_upperBlock = Block({ m_position.x, m_position.y + 1.0f, m_position.z }, *m_textureUpper);
    }

    void Character::Draw() const
    {
        m_lowerBlock.Draw();
        m_upperBlock.Draw();
    }

    bool Character::CheckCollision(const World& world, Vector3 newPos) const
    {
        Vector3 checkPoints[] = {
            newPos,
            {newPos.x, newPos.y + 1.0f, newPos.z}
        };

        for (auto& point : checkPoints)
        {
            // »спользуем floor вместо round дл€ правильного определени€ чанков
            int x = static_cast<int>(floorf(point.x));
            int z = static_cast<int>(floorf(point.z));

            if (world.HasSolidBlockAt(x, static_cast<int>(floorf(point.y)), z))
            {
                return true;
            }
        }
        return false;
    }
}