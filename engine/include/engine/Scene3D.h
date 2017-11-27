//
// Created by Андрей on 15.11.2017.
//

#ifndef YET_ANOTHER_ENGINE_SCENCE3D_H
#define YET_ANOTHER_ENGINE_SCENCE3D_H


#include "common/Singleton.h"

#include "AbstractObject.h"
#include "Camera.h"
#include "Listener.h"

#define CURRENT_SCENE3D Singleton<Scene3D>::instance()

class Scene3D
{
    friend class Singleton<Scene3D>;
public:
    void init();
    void start();

    void register_listener(short, BaseListener *);

    void emplace_object(AbstractObject*);
    // todo не очень удачное решение. Продумать концепцию с квалификаторами
    std::shared_ptr<AbstractObject> get_object(uint32_t);

    Camera& camera();
protected:
    GLFWwindow* window;
    std::vector<std::pair<short, std::unique_ptr<BaseListener>>> listeners;

    Camera _camera;
    std::vector<std::shared_ptr<AbstractObject>> objects;
private:
    Scene3D();

    static void key_callback(GLFWwindow*, int, int, int, int);
    bool press_keys[1024];
};

#endif //YET_ANOTHER_ENGINE_SCENCE3D_H
