//
// Created by Андрей on 15.11.2017.
//

#ifndef YET_ANOTHER_ENGINE_SCENCE3D_H
#define YET_ANOTHER_ENGINE_SCENCE3D_H


#include "AbstractObject.h"
#include "Camera.h"

template <typename T>
class Singleton {
public:
    static T& instance()
    {
        static T instance;
        return instance;
    }
    Singleton(Singleton const&) = delete;
    Singleton& operator= (Singleton const&) = delete;

private:
    Singleton() = default;
};

#define CURRENT_SCENE3D Singleton<Scene3D>::instance()

class Scene3D
{
    friend class Singleton<Scene3D>;
public:
    void init();
    void start();

    void emplace_object(AbstractObject*);
protected:
    GLFWwindow* window;
    std::vector<std::pair<short, std::function<void(Camera&)>>> key_handlers;

    Camera camera;
    std::vector<std::unique_ptr<AbstractObject>> objects;
private:
    Scene3D();

    static void key_callback(GLFWwindow*, int, int, int, int);
    bool press_keys[1024];
};

#endif //YET_ANOTHER_ENGINE_SCENCE3D_H
