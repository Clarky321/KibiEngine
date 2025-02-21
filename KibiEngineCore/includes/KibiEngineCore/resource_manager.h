#pragma once

#include <raylib.h>
#include <unordered_map>
#include <string>
#include <vector>
#include <mutex>

namespace KibiEngine
{
    class ResourceManager
    {
    public:
        static const Texture2D& LoadTexture(const std::string& path);
        static void PreloadAssets();
        static void UnloadAll();

    private:
        static std::unordered_map<std::string, Texture2D> m_textures;
        static std::vector<std::string> m_assetPaths;
        static std::mutex m_mutex;
    };
}