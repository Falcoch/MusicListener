#include "Buttons.hpp"

#include <imgui.h>

#include "../../../../include/stb/stb_image.h"

#include "../../interfaces/Player.hpp"

#include <iostream>

namespace tock::interface::player {
    Buttons::Buttons(Player * parent, float size)
    : Component(parent), _playButton(parent, size), _parameterButton(parent, size), _listButton(parent, size), _size(size) {
        int width = 0, height = 0, channels = 4;
        unsigned char * data = stbi_load("assets/texture/button/line.png", &width, &height, &channels, 0);
        this->_decoration.store(width, height, data, channels == 4 ? utils::Texture::RGBA : utils::Texture::RGB);
        stbi_image_free(data);
    }

    void Buttons::setPlaying(bool state) {
        this->_playButton.setPlaying(state);
    } 

    void Buttons::render(double time) {
        static float offset = (this->parent()->window().width() - (this->_size * 3.f))/3.9f;

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.f, 6.f));

        ImGui::Image((void*)(intptr_t)this->_decoration.identifier(), ImVec2(offset * 0.8f, this->_size));
        ImGui::SameLine();

        this->_parameterButton.render(time);
        ImGui::SameLine();

        ImGui::Image((void*)(intptr_t)this->_decoration.identifier(), ImVec2(offset, this->_size));
        ImGui::SameLine();

        this->_playButton.render(time);
        ImGui::SameLine();

        ImGui::Image((void*)(intptr_t)this->_decoration.identifier(), ImVec2(offset, this->_size));
        ImGui::SameLine();

        this->_listButton.render(time);
        ImGui::SameLine();

        ImGui::Image((void*)(intptr_t)this->_decoration.identifier(), ImVec2(offset * 0.8f, this->_size));
        
        ImGui::PopStyleVar(1);
    }
}