#include "Footer.hpp"

#include <imgui.h>
#include <tinyfiledialogs/tinyfiledialogs.h>

#include "../../interfaces/Player.hpp"

#include "../../../../include/stb/stb_image.h"

#include <iostream>

namespace tock::interface::player {
    Footer::Footer(Player * parent, float size)
    : Component(parent), _height(size) {}
    
    void Footer::render(double time) {
        float offset = static_cast<float>(this->parent()->window().width());

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));

        ImVec4 color = ImGui::GetStyleColorVec4(ImGuiCol_WindowBg);
        color.x *= 1.5f;
        color.y *= 1.5f;
        color.z *= 1.5f;

        ImGui::PushStyleColor(ImGuiCol_Button, color);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, color);
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, color);
        ImGui::PushStyleColor(ImGuiCol_FrameBg, color);
        ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(0.8f, 0.8f, 0.8f, 1.f));
        ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(0.8f, 0.8f, 0.8f, 1.f));

        color.x *= 1.25f;
        color.y *= 1.25f;
        color.z *= 1.25f;

        ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, color);
        ImGui::PushStyleColor(ImGuiCol_FrameBgActive, color);

        ImGui::Button("##Deoration_1", ImVec2(this->_height, this->_height));

        ImGui::SameLine();
        
        int volume = static_cast<int>(this->parent()->player().getVolume() * 100.f);
        ImGui::PushItemWidth(offset - (this->_height*2.f));

        color = ImGui::GetStyleColorVec4(ImGuiCol_Text);

        if(volume > 90) {
            color = ImVec4(9.f, 0.1f, 0.1f, 1.f);
        }
        else if(volume > 70) {
            color = ImVec4(9.f, 9.f, 0.1f, 1.f);
        }
        else if(volume > 50) {
            color = ImVec4(9.f, 0.9f, 0.5f, 1.f);
        }
        else if(volume > 25) {
            color = ImVec4(9.f, 0.9f, 0.75f, 1.f);
        }

        ImGui::PushStyleColor(ImGuiCol_Text, color);
        

        if(ImGui::SliderInt("##Volume", &volume, 0, 100, "%d%%")) {
            this->parent()->changeVolume(volume/100.f);
        }

        ImGui::SameLine();

        ImGui::Button("##Deoration_2", ImVec2(this->_height, this->_height));

        ImGui::PopStyleColor(9);
        ImGui::PopStyleVar(2);
    }  
}