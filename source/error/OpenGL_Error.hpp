#pragma once

#include <exception>
#include <GL/glew.h>
#include <iostream>
#include <source_location>

namespace tock::error {
    class opengl_error : public std::exception {
        private:
            GLenum _code;

        public:
            opengl_error();
            opengl_error(GLenum error);
           ~opengl_error();

            virtual const char * what() const noexcept;
            static void check(bool = false, std::ostream & = std::cerr, const std::source_location & = std::source_location::current());
    };

    
}