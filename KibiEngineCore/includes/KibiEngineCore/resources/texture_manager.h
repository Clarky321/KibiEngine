#pragma once

#include <raylib.h>

#include <KibiEngineCore\resources\resource_cache.h>

class TextureResource
{
public:
    bool Load(const std::string& path)
    {
        texture = LoadTexture(path.c_str());
        return texture.id != 0;
    }

    Texture2D texture;
};

class TextureManager : public ResourceCache<TextureResource> {};