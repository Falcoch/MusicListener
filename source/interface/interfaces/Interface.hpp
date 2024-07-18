#pragma once

namespace tock::interface {
    template <class T>
    class Interface {
        private:
            T * _parent;

        public:
            Interface() = delete;
            Interface(T * parent) : _parent(parent) {}
           ~Interface() = default;

            virtual void render(double) = 0;
            virtual void update(double) = 0;

            inline T * parent() const {return this->_parent;}
    };
}