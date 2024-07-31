#include "Buttons.hpp"

namespace tock::interface::list {
    Buttons::Buttons(List * parent)
    : Component(parent), _open(parent, 16.f), _erase(parent, 16.f) {
        int width = 0, height = 0, channels = 4;
        unsigned char * data = stbi_load("assets/texture/button/line.png", &width, &height, &channels, 0);
        this->_decoration.store(width, height, data, channels == 4 ? utils::Texture::RGBA : utils::Texture::RGB);
        stbi_image_free(data);
    }

    void Buttons::render(double time) {
        static float offset = (ImGui::GetWindowWidth() - 48.f) / 3.f;
        ImGui::SetCursorPos(ImVec2(0, 8.f));

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.f, 6.f));

        ImGui::Image((void*)(intptr_t)this->_decoration.identifier(), ImVec2(offset, 32.f));
        ImGui::SameLine();

        this->_open.render(time);
        ImGui::SameLine();

        ImGui::Image((void*)(intptr_t)this->_decoration.identifier(), ImVec2(offset, 32.f));
        ImGui::SameLine();

        this->_erase.render(time);
        ImGui::SameLine();

        ImGui::Image((void*)(intptr_t)this->_decoration.identifier(), ImVec2(offset, 32.f));
       
        ImGui::PopStyleVar(1);
    } 
}