//
// Created by Андрей on 19.11.2017.
//

#include <engine/Scene3D.h>

int main()
{
    Scene3D& scene = CURRENT_SCENE3D;
    scene.init();



    scene.start();
}
