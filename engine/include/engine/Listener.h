//
// Created by Андрей on 27.11.2017.
//

#ifndef YET_ANOTHER_ENGINE_LISTENER_H
#define YET_ANOTHER_ENGINE_LISTENER_H

#include <functional>

class BaseListener {
public:
    virtual void apply() const = 0;
};

template <typename T>
class Listener: public BaseListener
{
public:
    explicit Listener(T&, std::function<void(T&)>&&);

    void apply() const override;
protected:
    T& object;
    const std::function<void(T&)> handler;
};

template <typename T>
Listener<T>::Listener(T& object, std::function<void(T&)>&& handler):
        object(object), handler(handler) {}

template <typename T>
void Listener<T>::apply() const
{
    handler(object);
}

#endif //YET_ANOTHER_ENGINE_LISTENER_H
