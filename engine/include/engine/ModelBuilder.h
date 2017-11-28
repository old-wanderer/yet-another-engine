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

    ModelBuilder& begin_mesh(uint32_t);
    ModelBuilder& end_mesh();

    // TODO: продумать необходимость стратегий импорта
    ModelBuilder& import_from_file(const std::string&);
    ModelBuilder& push_back_vertex(glm::vec3, glm::vec3 = glm::vec3(0.5));
    ModelBuilder& push_back_vertex(vertex&);
    ModelBuilder &emplace_back_vertex(glm::vec3&&, glm::vec3&&, glm::vec2&&);
    ModelBuilder& set_color_vertex(unsigned int, glm::vec3);
    ModelBuilder& push_back_indices(unsigned int);
    ModelBuilder& push_back_all_indices(unsigned int*, unsigned int*);
    ModelBuilder& push_back_all_indices(std::initializer_list<unsigned int>);
    ModelBuilder &set_texture(Texture *);

    ModelBuilder& setProgram(ShaderProgram &program);

    Model* build();
protected:
    std::vector<Mesh> meshes;
    Mesh building_mesh { ShaderInputData::VERTEX };

    ShaderProgram* program = nullptr;
};


#endif //YET_ANOTHER_ENGINE_MODELBUILDER_H
