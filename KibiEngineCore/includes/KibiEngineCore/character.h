#pragma once

#include <raylib.h>
#include <KibiEngineCore\block.h>
#include <KibiEngineCore\world.h>
#include <KibiEngineCore\resource_manager.h>

namespace KibiEngine
{
    class Character
    {
    public:
        Character(Vector3 position); // конструктор - построить
        ~Character();                // деструктор - уничтожить (освободить)

        void Update(World& world);
        void Draw() const;
        Vector3 GetPosition() const { return m_position; }

    private:
        Vector3 m_position;
        Block m_lowerBlock;
        Block m_upperBlock;

        // Используем ссылки вместо указателей? пока что
        const Texture2D& m_textureLower;
        const Texture2D& m_textureUpper;
        //

        float m_moveSpeed = 0.2f;

        void UpdateBlocksPosition();
        bool CheckCollision(const World& world, Vector3 newPos) const;
    };
}