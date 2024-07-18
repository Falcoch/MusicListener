#pragma once

#include <GL/glew.h>
#include <compare>

namespace tock::utils {
    class Texture {
        private:
            GLuint _id;
            GLuint _type;
            mutable GLuint _slot;

        public:
            Texture(GLuint = 0, GLuint = GL_TEXTURE_2D);
            Texture(const Texture &) = delete;
            Texture & operator=(const Texture &) = delete;
           ~Texture();

            enum Wraping {
                REPEAT              = GL_REPEAT,
                MIRRORED_REPEAT     = GL_MIRRORED_REPEAT,
                CLAMP_TO_BORDER     = GL_CLAMP_TO_BORDER,
                CLAMP_TO_EDGE       = GL_CLAMP_TO_EDGE
            };

            enum Axis {
                S = 1,
                T = 2,
                R = 4
            };

            enum Format {
                AUTO,
                RGB     = GL_RGB,
                BGR     = GL_BGR,
                RGBA    = GL_RGBA,
                RED     = GL_RED,
                GREEN   = GL_GREEN,
                BLUE    = GL_BLUE,
            };

            void bind() const;
            void bind(GLuint) const;

            GLint width() const;
            GLint height() const;

            inline GLuint slot() const {return this->_slot;}
            inline GLuint type() const {return this->_type;}
            inline GLuint identifier() const {return this->_id;}

            void changeTextureSlot(GLuint);
            void setWraping(Wraping, uint32_t = S | T);
            void setSmoothing(bool);

            void release();
            void store(GLsizei, GLsizei, const void *, GLuint = RGBA);
            bool valid() const;

            bool operator==(const Texture &) const;
            bool operator!=(const Texture &) const;
            bool operator>=(const Texture &) const;
            bool operator<=(const Texture &) const;
            bool operator>(const Texture &) const;
            bool operator<(const Texture &) const;

            std::strong_ordering operator<=>(const Texture &) const;

            static void Unbind(GLuint = GL_TEXTURE_2D);

            
    };
}