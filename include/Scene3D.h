//
// Created by Андрей on 15.11.2017.
//

#ifndef YET_ANOTHER_ENGINE_SCENCE3D_H
#define YET_ANOTHER_ENGINE_SCENCE3D_H


#include "AbstractObject.h"
#include "Camera.h"

class Scene3D
{
public:
    void init();
    void start();

    void emplace_object(AbstractObject*);
protected:
    GLFWwindow* window;

    Camera camera;
    std::vector<std::unique_ptr<AbstractObject>> objects;
};


#endif //YET_ANOTHER_ENGINE_SCENCE3D_H
