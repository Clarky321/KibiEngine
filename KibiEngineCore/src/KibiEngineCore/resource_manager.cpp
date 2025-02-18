#include <KibiEngineCore\resource_manager.h>
#include <stdexcept>

namespace KibiEngine
{
	std::unordered_map<std::string, Texture2D> ResourceManager::m_textures;
	std::mutex ResourceManager::m_mutex;

	Texture2D& ResourceManager::LoadTexture(const std::string& path)
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		auto it = m_textures.find(path);
		if (it != m_textures.end())
		{
			return it->second;
		}

		Texture2D texture = ::LoadTexture(path.c_str());
		if (texture.id == 0)
		{
			throw std::runtime_error("Failed to load texture: " + path);
		}

		auto result = m_textures.emplace(path, texture);
		return result.first->second;
	}

	void ResourceManager::UnloadAll()
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		for (auto& pair : m_textures)
		{
			UnloadTexture(pair.second);
		}
		m_textures.clear();
	}
}