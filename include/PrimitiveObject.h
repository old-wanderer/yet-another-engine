//
// Created by Андрей on 16.10.17.
//

#ifndef YET_ANOTHER_ENGINE_PRIMITIVEOBJECT_HPP
#define YET_ANOTHER_ENGINE_PRIMITIVEOBJECT_HPP

#include "AbstractObject.h"

class PrimitiveObject: public AbstractObject
{
public:
    explicit PrimitiveObject(ShaderProgram&);
    void draw(glm::mat4) const override;

protected:
    GLuint _vbo_guid;
};


#endif //YET_ANOTHER_ENGINE_PRIMITIVEOBJECT_HPP
