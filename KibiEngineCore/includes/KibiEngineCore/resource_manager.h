#pragma once

#include <raylib.h>
#include <unordered_map>
#include <string>
#include <mutex>

namespace KibiEngine
{
    class ResourceManager
    {
    public:
        static Texture2D& LoadTexture(const std::string& path);
        static void UnloadAll();

    private:
        static std::unordered_map<std::string, Texture2D> m_textures;
        static std::mutex m_mutex;
    };
}