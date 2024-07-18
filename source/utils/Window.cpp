#include "Window.hpp"

#include <GLFW/glfw3.h>
#include <windows.h>

#include <iostream>

namespace tock::utils {
    Window::Window(const std::string & title, uint16_t width, uint16_t height)
    : _window(nullptr), _title(title), _width(width), _height(height) {
        glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
        std::cerr << "Construct Window" << std::endl;
    }

    Window::~Window() {
        std::cerr << "Destruct Window" << std::endl;
        this->close();
    }

    bool Window::isOpen() const {
        return this->_window != nullptr ? !glfwWindowShouldClose(this->_window) : false;
    }

    uint16_t Window::width() const {
        if(this->_window == nullptr) {
            return this->_width;
        }

        int width = this->_width;
        int height = 0;
        glfwGetWindowSize(this->_window, &width, &height);
        return width;
    }

    uint16_t Window::height() const {
        if(this->_window == nullptr) {
            return this->_height;
        }

        int width = 0;
        int height = this->_height;
        glfwGetWindowSize(this->_window, &width, &height);
        return height;
    }

    int Window::x() const {
        int x = 0;
        if(this->_window == nullptr) {
            int y = 0;
            glfwGetWindowPos(this->_window, &x, &y);
        }
        return x;
    }

    int Window::y() const {
        int y = 0;
        if(this->_window == nullptr) {
            int x = 0;
            glfwGetWindowPos(this->_window, &x, &y);
        }
        return y;
    }
    
    void Window::pollEvents() const {
        if(this->_window != nullptr) {
            glfwPollEvents();
        }
    }

    void Window::swapBuffers() const {
        if(this->_window != nullptr) {
            glfwSwapBuffers(this->_window);
        }
    }

    void Window::makeContextCurrent() const {
        if(this->_window != nullptr) {
            glfwMakeContextCurrent(this->_window);
        }
    }

    void Window::minimize() const {
        if(this->_window != nullptr) {
            glfwIconifyWindow(this->_window);
        }
    }

    void Window::setPosition(int x, int y) {
        if(this->_window != nullptr) {
            glfwGetWindowPos(this->_window, &x, &y);
        }
    }

    void Window::move(int x, int y) {
        if(this->_window != nullptr) {
            int pos_x = 0, pos_y = 0;
            glfwGetWindowPos(this->_window, &pos_x, &pos_y);
            glfwSetWindowPos(this->_window, pos_x + x, pos_y + y);
        }
    }

    void Window::open(Window * window) {
        if(this->_window == nullptr) {
            GLFWwindow * parent = window == nullptr ? NULL : window->address().value_or(nullptr);

            this->_window = glfwCreateWindow(this->_width, this->_height, this->_title.c_str(), NULL, parent);
            const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

            glfwSetWindowPos(this->_window, mode->width/2 - this->_width/2, mode->height/2 - this->_height/2);
            this->makeContextCurrent();
            glfwSwapInterval(1);          
        }
    }

    void Window::reload() {
        this->close();
        this->open();
    } 

    void Window::close() {
        if(this->_window != nullptr) {
            glfwSetWindowShouldClose(this->_window, true);
            glfwDestroyWindow(this->_window);
            this->_window = nullptr;
        }
    }
}