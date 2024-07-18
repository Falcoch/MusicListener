#pragma once

#include "../interfaces/Interface.hpp"

namespace tock::interface {
    template <class T>
    class Component : public Interface<T> {
        public:
            Component() = delete;
            Component(T * parent) : Interface<T>(parent) {}
           ~Component() = default;

            virtual void update(double) {};
    };
}