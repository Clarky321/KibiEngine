#pragma once

#include <raylib.h>

namespace KibiEngine
{
	class Block
	{
	public:
		Block();
		Block(Vector3 position, const Texture2D& texture);
		void Draw() const;

		Vector3 GetPosition() const { return m_position; }

	private:
		Vector3 m_position;
		Texture2D m_texture;
	};
}