//
// Created by Андрей on 17.10.17.
//

#ifndef YET_ANOTHER_ENGINE_MODEL_H
#define YET_ANOTHER_ENGINE_MODEL_H

#include <string>
#include <glm/glm.hpp>
#include <vector>
#include "Resource.h"

class Model: public Resource
{
public:
    explicit Model(const char*);
    void load() override;
    void unload() override;

    void drawModel() const;
protected:
    std::string _path_to_source;

    std::vector<glm::vec3>    _vertices; // нужно убрать из полей класса
    std::vector<unsigned int> _indexes;  // достаточно размера вектора
    GLuint _vao_guid;
    GLuint _vbo_guid;
    GLuint _ebo_guid;
};


#endif //YET_ANOTHER_ENGINE_MODEL_H