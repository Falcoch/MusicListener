#include "OpenGL_Error.hpp"

namespace tock::error {
    opengl_error::opengl_error() 
    : opengl_error(glGetError()) {}

    opengl_error::opengl_error(GLenum code) 
    : _code(code) {}

    opengl_error::~opengl_error() {}

    const char * opengl_error::what() const noexcept {
        switch (this->_code) {
            case GL_NO_ERROR:
                return "GL NO ERROR";
            
            case GL_INVALID_ENUM:
                return "GL INVALIDE ENUM";

            case GL_INVALID_VALUE:
                return "GL INVALID VALUE";

            case GL_INVALID_OPERATION:
                return "GL INVALID OPERATION";

            case GL_STACK_OVERFLOW:
                return "GL STACK OVERFLOW";

            case GL_STACK_UNDERFLOW:
                return "GL STACK UNDERFLOW";

            case GL_OUT_OF_MEMORY:
                return "GL OUT OF MEMORY";

            case GL_INVALID_FRAMEBUFFER_OPERATION:
                return "GL INVALID FRAMEBUFFER OPERATION";

            case GL_CONTEXT_LOST:
                return "GL CONTEXT LOST";
        
            default:
                return "UNKNOWN GL ERROR";
        }
    }

    void opengl_error::check(bool throws, std::ostream & os, const std::source_location & location) {
        GLenum error = glGetError();
        if(error != GL_NO_ERROR) {
            error::opengl_error exception(error);
            if(throws) {
                throw exception;
            }
        }
    }
}