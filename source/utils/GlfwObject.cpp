#include "GlfwObject.hpp"

#include <GLFW/glfw3.h>
#include <stdexcept>

namespace tock::utils {
    bool GlfwObject::_Initilized = false;

    GlfwObject::GlfwObject() {
        if(!GlfwObject::_Initilized) {
            if(glfwInit() != GLFW_TRUE) {
                throw std::runtime_error("Failled to initialize GLFW.");
            }
            GlfwObject::_Initilized = true;
        }
    }
}