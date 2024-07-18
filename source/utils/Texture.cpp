#include "Texture.hpp"

#include <exception>
#include <iostream>

namespace tock::utils {
    Texture::Texture(GLuint slot, GLuint type) 
    : _id(0), _type(type), _slot(slot) {
        
    }

    Texture::~Texture() {
        if(this->valid()) {
            glDeleteTextures(1, &this->_id);
        }
    }

    void Texture::bind() const {
        if(this->valid()) {
            glActiveTexture(GL_TEXTURE0 + this->_slot);
            glBindTexture(this->_type, this->_id);
        }
    }

    void Texture::bind(GLuint slot) const {
        if(this->valid()) {
            this->_slot = slot;
            this->bind();
        }
    }

    GLint Texture::width() const {
        if(this->_id == 0) {
            throw std::runtime_error("Void texture.");
        }

        GLint width;
        glGetTexLevelParameteriv(this->_type, 0, GL_TEXTURE_WIDTH, &width);
        return width;
    }

    GLint Texture::height() const {
        if(this->_id == 0) {
            throw std::runtime_error("Void texture.");
        }

        GLint height;
        glGetTexLevelParameteriv(this->_type, 0, GL_TEXTURE_HEIGHT, &height);
        return height;
    }

    void Texture::changeTextureSlot(GLuint slot) {
        this->_slot = slot;
    }

    void Texture::setWraping(Wraping wraping, uint32_t flags) {
        glBindTexture(this->_type, this->_id);
        if(flags != 0) {
            if((flags & S) != 0) {
                glTexParameteri(this->_type, GL_TEXTURE_WRAP_S, wraping);
            }

            if((flags & T) != 0) {
                glTexParameteri(this->_type, GL_TEXTURE_WRAP_T, wraping);
            }

            if((flags & R) != 0) {
                glTexParameteri(this->_type, GL_TEXTURE_WRAP_R, wraping);
            }
        }
    }

    void Texture::setSmoothing(bool state) {
        glBindTexture(this->_type, this->_id);
        glTexParameteri(this->_type, GL_TEXTURE_MIN_FILTER, state ? GL_LINEAR : GL_NEAREST);
        glTexParameteri(this->_type, GL_TEXTURE_MAG_FILTER, state ? GL_LINEAR : GL_NEAREST);
    }

    void Texture::release() {
        glDeleteTextures(1, &this->_id);
        this->_id = 0;
    }

    void Texture::store(GLsizei width, GLsizei height, const void * data, GLuint format) {
        if(this->valid()) {
            glDeleteTextures(1, &this->_id);
        }
        glGenTextures(1, &this->_id);
        
        glBindTexture(this->_type, this->_id);
        glTexImage2D(this->_type, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

        this->setWraping(CLAMP_TO_BORDER, S | T );
        this->setSmoothing(true);
    }

    bool Texture::valid() const {
        return this->_id != 0;
    }

    bool Texture::operator==(const Texture & texture) const {
        return this->_id == texture._id;
    }

    bool Texture::operator!=(const Texture & texture) const {
        return this->_id != texture._id;
    }

    bool Texture::operator>=(const Texture & texture) const {
        return this->_id >= texture._id;
    }

    bool Texture::operator<=(const Texture & texture) const {
        return this->_id <= texture._id;
    }

    bool Texture::operator>(const Texture & texture) const {
        return this->_id > texture._id;
    }

    bool Texture::operator<(const Texture & texture) const {
        return this->_id < texture._id;
    }

    std::strong_ordering Texture::operator<=>(const Texture & texture) const {
        return this->_id <=> texture._id;
    }

    void Texture::Unbind(GLuint type) {
        glBindTexture(type, 0);
    }
}