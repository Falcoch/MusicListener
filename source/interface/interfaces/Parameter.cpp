#include "Parameter.hpp"

#include <imgui.h>
#include <iostream>

namespace tock::interface {
    Parameter::Parameter(Renderer & manager, utils::Window & window) 
    : Interface(manager), 
      _window(window),
      _titlebar(this) {
        std::cout << "Construct Parameter Interface" << std::endl;
    }

    Parameter::~Parameter() {
        std::cout << "Destruct Parameter Interface" << std::endl;
    }

    void Parameter::close() {
        this->parent()->fall(*this);
    }

    void Parameter::render(double time) {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.f, 0.f));

        if(ImGui::Begin("##Parameter", NULL, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysUseWindowPadding)) {
            this->_titlebar.render(time);

            ImGui::Text("Hello Parameter !");

            if(ImGui::Button("Save")) {
                this->close();
            }
        }
        ImGui::End();

        ImGui::PopStyleVar(2);
    }

    void Parameter::update(double) {

    }
}