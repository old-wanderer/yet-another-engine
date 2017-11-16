//
// Created by Андрей on 01.11.17.
//

#include "engine/TexturedModel.h"

struct vert {
    glm::vec3 cord;
    glm::vec2 text;
};

TexturedModel::TexturedModel(ShaderProgram &program, Texture& texture):
        Model(program), texture(texture)
{
    _vertices.push_back({glm::vec3( 0.5f,  0.5f, 0.0f)});
    _vertices.push_back({glm::vec3( 0.5f, -0.5f, 0.0f)});
    _vertices.push_back({glm::vec3(-0.5f, -0.5f, 0.0f)});
    _vertices.push_back({glm::vec3(-0.5f,  0.5f, 0.0f)});

    _indexes.insert(_indexes.end(), {0, 1, 3, 1, 2, 3});
}

void TexturedModel::load()
{
    if (this->_isLoaded) return;

    std::vector<vert> new_vert = {
            {glm::vec3( 0.5f,  0.5f, 0.0f), glm::vec2(5.0f, 5.0f)},
            {glm::vec3( 0.5f, -0.5f, 0.0f), glm::vec2(5.0f, 0.0f)},
            {glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(0.0f, 0.0f)},
            {glm::vec3(-0.5f,  0.5f, 0.0f), glm::vec2(0.0f, 5.0f)}
    };

    glGenVertexArrays(1, &this->_vao_guid);
    glGenBuffers(1, &this->_vbo_guid);
    glGenBuffers(1, &this->_ebo_guid);

    glBindVertexArray(this->_vao_guid);
    glBindBuffer(GL_ARRAY_BUFFER, this->_vbo_guid);
    glBufferData(GL_ARRAY_BUFFER, new_vert.size() * sizeof(vert), &new_vert[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_ebo_guid);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indexes.size() * sizeof(unsigned int), &_indexes[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vert), nullptr);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vert), (GLvoid*)sizeof(vert::cord));


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    this->_isLoaded = true;
}

void TexturedModel::unload()
{
    Model::unload();
}

void TexturedModel::drawModel(glm::mat4 proj_view, glm::mat4 model) const
{
    glBindTexture(GL_TEXTURE_2D, this->texture.guid());
//    glUniform1i(glGetUniformLocation(program.guid(), "texture0"), 0);
    Model::drawModel(proj_view, model);
}

