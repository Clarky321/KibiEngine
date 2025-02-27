#pragma once

#include <raylib.h>
#include <unordered_map>
#include <string>
#include <vector>
#include <mutex>
#include <KibiEngineCore\npc_models.h>

namespace KibiEngine
{
    class ResourceManager
    {
    public:
        static const Texture2D& LoadTexture(const std::string& path);
        static void PreloadAssets();
        static void UnloadAll();

        static const std::unordered_map<std::string, Texture2D>& GetTextures()
        {
            return m_textures;
        }

        //
        static std::unordered_map<std::string, std::unique_ptr<VoxModel>> m_voxModels;
        //

    private:
        static std::unordered_map<std::string, Texture2D> m_textures;
        static std::vector<std::string> m_assetPaths;
        static std::mutex m_mutex;

        //
        static const VoxModel* LoadVoxModel(const std::string& path);
        static void UnloadVoxModels();
        //
    };
}