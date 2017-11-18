//
// Created by Андрей on 01.11.17.
//

#ifndef YET_ANOTHER_ENGINE_TEXTUREDMODEL_H
#define YET_ANOTHER_ENGINE_TEXTUREDMODEL_H


#include "Model.h"
#include "Texture.h"

class TexturedModel: public Model
{
public:
    TexturedModel(ShaderProgram&, Texture&);

    void load() override;
    void unload() override;

    void drawModel(glm::mat4, glm::mat4) const override;
protected:
    Texture& texture;
};


#endif //YET_ANOTHER_ENGINE_TEXTUREDMODEL_H
