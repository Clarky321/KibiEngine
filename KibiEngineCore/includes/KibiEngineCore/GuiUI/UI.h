#pragma once

#include <raylib.h>

namespace KibiEngine
{
    class UI
    {
    public:
        static void Initialize();
        static void Shutdown();
        static void Draw(Texture2D* currentTexture, bool* showWireframe);
    };
}