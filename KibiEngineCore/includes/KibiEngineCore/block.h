#pragma once

#include <raylib.h>

namespace KibiEngine
{
	class Block
	{
	public:
		Block();
		Block(Vector3 position, Texture2D texture);
		void Draw() const;

	private:
		Vector3 m_position;
		Texture2D m_texture;
	};
}