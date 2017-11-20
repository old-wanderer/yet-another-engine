//
// Created by Андрей on 17.10.17.
//

#ifndef YET_ANOTHER_ENGINE_MODEL_H
#define YET_ANOTHER_ENGINE_MODEL_H

#include <string>
#include <glm/glm.hpp>
#include <vector>
#include "Resource.h"
#include "ShaderProgram.h"
#include "Mesh.h"

class Model: public Resource
{
    friend class ModelBuilder;
public:
    void load() override;
    void unload() override;

    virtual void drawModel(glm::mat4, glm::mat4) const;
protected:
    explicit Model(ShaderProgram&);

    ShaderProgram& program;
    std::vector<Mesh> meshes;
};


#endif //YET_ANOTHER_ENGINE_MODEL_H
