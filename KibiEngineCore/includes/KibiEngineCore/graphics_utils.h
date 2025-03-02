#pragma once

#include <raylib.h>

namespace KibiEngine
{
    namespace Graphics
    {
        void DrawCubeTexture
        (
            Texture2D texture,
            Vector3 position,
            float width,
            float height,
            float length,
            Color color
        );

        void DrawCubeTextureRec
        (
            Texture2D texture,
            Rectangle source,
            Vector3 position,
            float width,
            float height,
            float length,
            Color color
        );
    }
}