//
// Created by Андрей on 31.10.17.
//

#ifndef YET_ANOTHER_ENGINE_TEXTURE_H
#define YET_ANOTHER_ENGINE_TEXTURE_H


#include <engine/Resource.h>
#include <string>

class Texture: public Resource<PathLoadContext>
{
public:
    explicit Texture(const std::string&);
    explicit Texture(std::string&&);

    void load() override;
    void unload() override;
};


#endif //YET_ANOTHER_ENGINE_TEXTURE_H
