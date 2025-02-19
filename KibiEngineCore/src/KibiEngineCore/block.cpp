#include <KibiEngineCore\block.h>
#include <KibiEngineCore\graphics_utils.h>

namespace KibiEngine
{
    Block::Block() : m_position{ 0, 0, 0 }, m_texture{ 0 } {}

    Block::Block(Vector3 position, const Texture2D& texture)
        : m_position(position), m_texture(texture) {}

    void Block::Draw() const
    {
        Graphics::DrawCubeTexture(m_texture, m_position, 1.0f, 1.0f, 1.0f, WHITE);
    }
}