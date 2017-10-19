//
// Created by Андрей on 16.10.17.
//

#ifndef YET_ANOTHER_ENGINE_ABSTRACTOBJECT_H
#define YET_ANOTHER_ENGINE_ABSTRACTOBJECT_H

#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>


class AbstractObject
{
public:
    AbstractObject();
    virtual ~AbstractObject();
    virtual void draw() const = 0;

protected:
    std::vector<glm::vec3> vertices;
    GLuint _vao_guid;
};


#endif //YET_ANOTHER_ENGINE_ABSTRACTOBJECT_H
