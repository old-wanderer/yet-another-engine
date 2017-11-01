//
// Created by Андрей on 01.11.17.
//

#include "TexturedModel.h"

struct vert {
    glm::vec3 cord;
    glm::vec2 text;
};

TexturedModel::TexturedModel(ShaderProgram &program, Texture& texture):
        Model(program), texture(texture)
{

    //  0.5f,  0.5f, 0.0f, 1.0f, 1.0f,   // Верхний правый
    //  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,   // Нижний правый
    // -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,   // Нижний левый
    // -0.5f,  0.5f, 0.0f, 0.0f, 1.0f    // Верхний левый
    _vertices.push_back({glm::vec3( 0.5f,  0.5f, 0.0f)});
    _vertices.push_back({glm::vec3( 0.5f, -0.5f, 0.0f)});
    _vertices.push_back({glm::vec3(-0.5f, -0.5f, 0.0f)});
    _vertices.push_back({glm::vec3(-0.5f,  0.5f, 0.0f)});

    _indexes.insert(_indexes.end(), {0, 1, 3, 1, 2, 3});
}

void TexturedModel::load()
{
    if (this->_isLoaded) return;

    uint32_t data_offset = sizeof(glm::vec3) + sizeof(glm::vec2);
    auto row_data = new uint8_t[data_offset * _vertices.size()];

    glm::vec2 text_coord[4] = {
            glm::vec2(1.0f, 1.0f),
            glm::vec2(1.0f, 0.0f),
            glm::vec2(0.0f, 0.0f),
            glm::vec2(0.0f, 1.0f)
    };

    for (int i = 0; i < _vertices.size(); i++)
    {
        std::memcpy(row_data + i * data_offset, &_vertices[i].coordinate, sizeof(glm::vec3));
        std::memcpy(row_data + i * data_offset + sizeof(glm::vec3), &text_coord[i], sizeof(glm::vec2));
    }

    std::vector<vert> new_vert = {
            {glm::vec3( 0.5f,  0.5f, 0.0f), glm::vec2(1.0f, 1.0f)},
            {glm::vec3( 0.5f, -0.5f, 0.0f), glm::vec2(1.0f, 0.0f)},
            {glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(0.0f, 0.0f)},
            {glm::vec3(-0.5f,  0.5f, 0.0f), glm::vec2(0.0f, 1.0f)}
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
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->texture.guid());
    glUniform1i(glGetUniformLocation(program.guid(), "texture0"), 0);
    Model::drawModel(proj_view, model);
}

