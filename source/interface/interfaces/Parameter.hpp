#pragma once

#include <GL/glew.h>

#include "Interface.hpp"
#include "../Renderer.hpp"
#include "../components/parameter/Titlebar.hpp"
#include "../../utils/Window.hpp"

namespace tock::interface {
    class Parameter : public Interface<Renderer> {
        private:
            utils::Window & _window;

            parameter::Titlebar _titlebar;

        public:
            Parameter(Renderer & manager, utils::Window &);
           ~Parameter();

            inline utils::Window & window() {return this->_window;}
            
            void close();

            void render(double); 
            void update(double);
    };
}