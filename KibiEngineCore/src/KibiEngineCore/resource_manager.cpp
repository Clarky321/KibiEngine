#include <stdexcept>

#include <KibiEngineCore\resource_manager.h>
#include <KibiEngineCore\npc_models.h>

namespace KibiEngine
{
	std::unordered_map<std::string, Texture2D> ResourceManager::m_textures;
	std::vector<std::string> ResourceManager::m_assetPaths =
	{
		"../../assets/tileset/dirt.png",
		"../../assets/tileset/orangewool.png",
		"../../assets/tileset/woolcoloredblue.png",
		"../../assets/tileset/sand.png",
		"../../assets/tileset/wood.png"

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

	//
	std::unordered_map<std::string, std::unique_ptr<VoxModel>> ResourceManager::m_voxModels;

	const VoxModel* ResourceManager::LoadVoxModel(const std::string& path)
	{
		if (auto it = m_voxModels.find(path); it != m_voxModels.end())
		{
			return it->second.get();
		}

		auto model = std::make_unique<VoxModel>(path);
		m_voxModels[path] = std::move(model);
		return m_voxModels[path].get();
	}

	void ResourceManager::UnloadVoxModels()
	{
		m_voxModels.clear();
	}
	//
}