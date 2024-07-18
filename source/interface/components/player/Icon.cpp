#include "Icon.hpp"

#include <cmath>
#include <imgui.h>

#include "../../interfaces/Player.hpp"
#include "../../../audio/MetaData.hpp"
#include "../../../error/OpenGL_Error.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../../../../include/stb/stb_image.h"

#include <iostream>

namespace tock::interface::player {
    Icon::Icon(Player * parent, const std::string & message)
    : Component(parent), _icon(), _defaultMessage(message) {
        this->_icon = std::make_unique<utils::Texture>();

        int width = 0, height = 0, channels = 0;
        unsigned char * data = stbi_load("assets/texture/overlay/circle.png", &width, &height, &channels, 0);
        this->_overlay.store(width, height, data, utils::Texture::RGBA);
        stbi_image_free(data);

        data = stbi_load("assets/texture/overlay/paused.png", &width, &height, &channels, 0);
        this->_paused.store(width, height, data, utils::Texture::RGBA);
        stbi_image_free(data);
    }

    void Icon::load(const audio::Sound & sound) {
        audio::MetaData data(sound);
        if(data.empty()) {
            return;
        }

        std::optional<FMOD_TAG> tag = data.get("APIC");
        if(tag.has_value()) {
            int width = 0, height = 0, channels = 4;
            unsigned int size = tag.value().datalen;
            
            char * start = static_cast<char *>(tag.value().data);
            
            ++start;
            --size;

            while(*start != '\0') {
                ++start;
                --size;
            }

            start += 2;
            size -= 2;

            while(*start != '\0') {
                ++start;
                --size;
            }

            ++start;
            --size;

            unsigned char * data = stbi_load_from_memory((unsigned char *)(start), size, &width, &height, &channels, 0);
            
            if(data == NULL) {
                throw std::runtime_error(stbi_failure_reason());
            }

            this->_icon->store(width, height, data, channels == 4 ? utils::Texture::RGBA : utils::Texture::RGB);

            stbi_image_free(data);
            error::opengl_error::check();
        }
        else {
            this->_icon->release();
        }
    }

    void Icon::unload() {
        this->_icon->release();
    }

    void Icon::render(double) {
        uint16_t size = this->parent()->window().width();
        if(this->_icon->valid()) {
            ImVec2 p = ImGui::GetCursorScreenPos();
            ImGui::Image((void*)(intptr_t)this->_icon->identifier(), ImVec2(size, size));
            ImGui::GetWindowDrawList()->AddImage((void*)(intptr_t) this->_overlay.identifier(), p, ImVec2(size, size+25.f));
            if(this->parent()->player().isPausing()) {
                ImGui::GetWindowDrawList()->AddImage((void*)(intptr_t) this->_paused.identifier(), p, ImVec2(size, size+25.f));
            }
        }
        else {
            ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyleColorVec4(ImGuiCol_WindowBg));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImGui::GetStyleColorVec4(ImGuiCol_WindowBg));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImGui::GetStyleColorVec4(ImGuiCol_WindowBg));
            ImGui::Button(this->_defaultMessage.c_str(), ImVec2(size, size));
            ImGui::PopStyleColor(3);

            if(ImGui::IsItemClicked()) {
                this->parent()->load();
            }
        }
    }
}