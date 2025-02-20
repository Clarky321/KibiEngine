#pragma once

#include <unordered_map>
#include <memory>
#include <mutex>

template<typename T>

class ResourceCache
{
public:
    template<typename... Args>

    T& Load(const std::string& key, Args&&... args)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = cache_.find(key);

        if (it == cache_.end())
        {
            auto resource = std::make_unique<T>();

            if (!resource->Load(std::forward<Args>(args)...))
            {
                throw std::runtime_error("Failed to load resource: " + key);
            }
            cache_[key] = std::move(resource);
        }
        return *cache_[key];
    }

    void UnloadAll()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        cache_.clear();
    }

private:
    std::unordered_map<std::string, std::unique_ptr<T>> cache_;
    std::mutex mutex_;
};