#include "Button.hpp"


#include <imgui.h>
#include "../../include/stb/stb_image.h"

namespace tock::interface {
    template <class T>
    Button<T>::Button(T * parent, const std::string & title, float size, const std::string & path)
    : Component<T>(parent), _icon(nullptr), _title(title), _size(size) {
        if(!path.empty()) {
            this->_icon = std::make_unique<utils::Texture>();
            int width = 0, height = 0, channels = 0;
            unsigned char * data = stbi_load(path.c_str(), &width, &height, &channels, 0);
            this->_icon->store(width, height, data, utils::Texture::RGBA);
            stbi_image_free(data);
        }
    }

    template <class T>
    void Button<T>::render(double time) {
        if(this->_icon.get() != nullptr) {
            if(ImGui::ImageButton((void*)(intptr_t) this->_icon->identifier(), ImVec2(this->_size, this->_size))) {
                this->onPressed(time);
            }
        }
        else {
            if(ImGui::Button(this->_title.c_str(), ImVec2(this->_size, this->_size))) {
                this->onPressed(time);
            }
        }
    }
}