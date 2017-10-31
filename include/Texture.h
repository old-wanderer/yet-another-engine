//
// Created by Андрей on 31.10.17.
//

#ifndef YET_ANOTHER_ENGINE_TEXTURE_H
#define YET_ANOTHER_ENGINE_TEXTURE_H


#include <Resource.h>
#include <string>

class Texture: public Resource
{
public:
    Texture(std::string&&);

    void load() override;
    void unload() override;

protected:
    std::string path;
};


#endif //YET_ANOTHER_ENGINE_TEXTURE_H
