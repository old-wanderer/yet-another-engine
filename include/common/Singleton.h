//
// Created by Андрей on 17.11.2017.
//

#ifndef YET_ANOTHER_ENGINE_SINGLETON_H
#define YET_ANOTHER_ENGINE_SINGLETON_H

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

#endif //YET_ANOTHER_ENGINE_SINGLETON_H
