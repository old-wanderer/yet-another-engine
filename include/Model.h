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
    void load() override;

    void unload() override;
    void drawModel() const;

    static Model* from_file(const std::string&);
    static Model* from_rectangle(GLfloat, GLfloat, glm::vec3);
protected:
    Model(std::vector<glm::vec3>&&, std::vector<unsigned int>&&);

    std::vector<glm::vec3>    _vertices;
    std::vector<unsigned int> _indexes;
    GLuint _vao_guid;
    GLuint _vbo_guid;
    GLuint _ebo_guid;
};


#endif //YET_ANOTHER_ENGINE_MODEL_H
