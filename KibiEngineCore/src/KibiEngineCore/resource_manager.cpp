#include <KibiEngineCore\resource_manager.h>
#include <stdexcept>

namespace KibiEngine
{
	std::unordered_map<std::string, Texture2D> ResourceManager::m_textures;
	std::vector<std::string> ResourceManager::m_assetPaths = {
		"../../assets/tileset/dirt.png",
		"../../assets/tileset/orangewool.png",
		"../../assets/tileset/woolcoloredblue.png"
	};
	std::mutex ResourceManager::m_mutex;

	const Texture2D& ResourceManager::LoadTexture(const std::string& path)
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		if (auto it = m_textures.find(path); it != m_textures.end())
		{
			return it->second;
		}

		Texture2D texture = ::LoadTexture(path.c_str());
		if (texture.id == 0)
		{
			throw std::runtime_error("Failed to load texture: " + path);
		}

		m_textures[path] = texture;
		return m_textures[path];
	}

	void ResourceManager::PreloadAssets()
	{
		for (const auto& path : m_assetPaths)
		{
			LoadTexture(path);
		}
	}

	void ResourceManager::UnloadAll()
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		for (auto& [path, texture] : m_textures)
		{
			UnloadTexture(texture);
		}
		m_textures.clear();
	}
}