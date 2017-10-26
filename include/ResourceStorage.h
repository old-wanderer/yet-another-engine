//
// Created by Андрей on 16.10.17.
//

#ifndef YET_ANOTHER_ENGINE_RESOURCESTORAGE_HPP
#define YET_ANOTHER_ENGINE_RESOURCESTORAGE_HPP

#include <type_traits>
#include <map>
#include <string>
#include "Resource.h"

template <typename T>
class ResourceStorage final
{
    static_assert(std::is_base_of<Resource, T>::value, "wrong type");
public:
    ResourceStorage() = default;
    virtual ~ResourceStorage() = default;

    T& get(std::string key);

    template <class ...Args>
    void emplace(const std::string&, Args&& ...args);
    void emplace(const std::string&, T*);
private:
    std::map<std::string, std::unique_ptr<T>> resources;
};

template <typename T>
template <class ...Args>
void ResourceStorage<T>::emplace(const std::string &key, Args &&... args)
{
    resources.emplace(std::forward<const std::string>(key),
                      std::unique_ptr<T>(new T(std::forward<Args>(args)...)));
}

template <typename T>
void ResourceStorage<T>::emplace(const std::string &key, T *value)
{
    resources.emplace(std::forward<const std::string>(key),
                      std::unique_ptr<T>(value));
}

template <typename T>
T& ResourceStorage<T>::get(const std::string key)
{
    auto point = resources.find(key);
    if (point == resources.end())
    {
        throw std::out_of_range("cant find resource");
    }

    T& resource = *point->second;
    if (!resource.isLoaded())
    {
        resource.load();
    }

    return resource;
}

#endif //YET_ANOTHER_ENGINE_RESOURCESTORAGE_HPP
