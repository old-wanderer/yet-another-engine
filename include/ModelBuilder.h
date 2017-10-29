//
// Created by Андрей on 29.10.17.
//

#ifndef YET_ANOTHER_ENGINE_MODELBUILDER_H
#define YET_ANOTHER_ENGINE_MODELBUILDER_H


#include <glm/vec3.hpp>
#include <vector>
#include "ShaderProgram.h"
#include "Model.h"

class ModelBuilder
{
public:
    ModelBuilder() = default;

    // TODO: продумать необходимость стратегий импорта
    ModelBuilder& import_from_file(const std::string&);
    ModelBuilder& push_back_vertex(glm::vec3, glm::vec3 = glm::vec3(0.5));
    ModelBuilder& push_back_vertex(vertex);
    ModelBuilder& set_color_vertex(unsigned int, glm::vec3);
    ModelBuilder& push_back_indices(unsigned int);
    ModelBuilder& push_back_all_indices(unsigned int*, unsigned int*);
    ModelBuilder& push_back_all_indices(std::initializer_list<unsigned int>);

    ModelBuilder& setProgram(ShaderProgram &program);

    Model* build();
protected:
    std::vector<vertex>       vertices;
    std::vector<unsigned int> indices;

    ShaderProgram* program = nullptr;
};


#endif //YET_ANOTHER_ENGINE_MODELBUILDER_H