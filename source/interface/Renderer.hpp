#pragma once

#include <GL/glew.h>

#include <stack>
#include <memory>
#include <optional>
#include <vector>

#include "interfaces/Interface.hpp"
#include "components/Component.hpp"

#include "../utils/Window.hpp"

namespace tock::interface {
    class Renderer : public Interface<Renderer> {
        private:
            utils::Window & _window;
            std::vector<std::reference_wrapper<Interface<Renderer>>> _subscriber;
            std::stack<std::reference_wrapper<Interface<Renderer>>> _children;

        public:
            Renderer() = delete;
            Renderer(utils::Window &);
           ~Renderer();

            inline std::stack<std::reference_wrapper<Interface<Renderer>>> & children() {return this->_children;}
            inline utils::Window & window() {return this->_window;}

            inline void push(Interface<Renderer> & interface) {this->_children.push(interface);}
            inline void pop() {this->_children.pop();}
            void fall(Interface<Renderer> &);

            void subscribe(Interface<Renderer> &);
            void unsubscribe(Interface<Renderer> &);
            
            inline void setWindow(const utils::Window & window) {this->_window = window;}

            void moveWindow(int x, int y) {this->_window.move(x, y);}
            
            void show(double);

            virtual void render(double);
            virtual void update(double);
    };
}