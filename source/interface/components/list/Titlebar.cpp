#include "Titlebar.hpp"

#include <imgui.h>

#include "../../interfaces/List.hpp"

namespace tock::interface::list {
    Titlebar::Titlebar(List * parent, float height)
    : Component(parent), _height(height) {}

    void Titlebar::render(double) {
        float offset = static_cast<float>(this->parent()->window().width()) / 10.f;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
        
        if(ImGui::Button("Close", ImVec2(offset * 1.5f, this->_height))) {
            this->parent()->close();
        }

        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImGui::GetStyleColorVec4(ImGuiCol_Button));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImGui::GetStyleColorVec4(ImGuiCol_Button));

        ImGui::SameLine();

        ImGui::Button("##Movebar", ImVec2(offset*6.5f, this->_height));
        if(ImGui::IsItemActive()) {
            ImVec2 delta = ImGui::GetMouseDragDelta();
            this->parent()->parent()->moveWindow(static_cast<int>(delta.x), static_cast<int>(delta.y));
        }

        ImGui::PopStyleColor(2);
        ImGui::SameLine();

        if(ImGui::Button("-", ImVec2(offset, this->_height))) {
            this->parent()->window().minimize();
        }
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.95f, 0.1f, 0.15f, 1.f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.95f, 0.1f, 0.15f, 1.f));
        if(ImGui::Button("x", ImVec2(offset, this->_height))) {
            this->parent()->parent()->window().close();
        }
        ImGui::PopStyleColor(2);

        ImGui::PopStyleVar(2);
    }   
}