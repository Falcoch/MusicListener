#pragma once

#include "GlfwObject.hpp"

#include <GLFW/glfw3.h>
#include <string>
#include <optional>

namespace tock::utils {
    class Window : public utils::GlfwObject {
        private:
            GLFWwindow * _window;
            std::string _title;
            uint16_t _width, _height;

        public:
            Window() = delete;
            Window(const std::string &, uint16_t, uint16_t);
           ~Window();

            inline std::optional<GLFWwindow *> address() const {return this->_window;}

            bool isOpen() const;
            uint16_t width() const;
            uint16_t height() const;

            int x() const;
            int y() const;

            void pollEvents() const;
            void swapBuffers() const;
            void makeContextCurrent() const;
            void minimize() const;

            void setPosition(int, int);
            void move(int, int);

            void open(Window * = nullptr);
            void reload();
            void close();

            inline static double CurrentTime() {return glfwGetTime();}
    };
}