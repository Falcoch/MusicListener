#pragma once

#include <GL/glew.h>

#include <memory>
#include <string>

#include "components/Component.hpp"
#include "../utils/Texture.hpp"

namespace tock::interface {
    template <class T>
    class Button : public Component<T> {
        private:
            std::unique_ptr<utils::Texture> _icon;
            std::string _title;
            float _size;

        public:
            Button() = delete;
            Button(T *, const std::string & title, float = 24.f, const std::string & = "");
   virtual ~Button() = default;

            inline const utils::Texture & icon() const {return this->_icon;}
            inline float size() const {return this->_size;}

            inline void setSize(float size) {this->_size = size;}

            void render(double) override final;
            virtual void onPressed(double) = 0;
    };
}

#include "Button.tpp"