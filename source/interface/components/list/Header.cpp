#include "Header.hpp"

#include <string>
#include <imgui.h>

#include "../../interfaces/List.hpp"
#include "../../interfaces/Player.hpp"

namespace tock::interface::list {
    Header::Header(List * parent)
    : Component(parent) {}

    void Header::render(double time) {
        List * parent = this->parent();
        if(parent == nullptr) {
            return;
        }

        auto current = parent->playing();
        std::string text = "";
        if(current.has_value()) {
            text = "Currently Playing : ";
            text.append(current.value().get().title());            
        }
        else {
            text = "Nothing is Playing !";
        }

        float textWidth = ImGui::CalcTextSize(text.c_str()).x;
        ImGui::SetCursorPos(ImVec2(ImGui::GetWindowWidth() / 2.f - textWidth/2.f, ImGui::GetCursorPosY()));
        ImGui::Text(text.c_str());
    } 
}