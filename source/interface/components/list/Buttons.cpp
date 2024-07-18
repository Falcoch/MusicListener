#include "Buttons.hpp"

namespace tock::interface::list {
    Buttons::Buttons(List * parent)
    : Component(parent), _open(parent, 16.f), _erase(parent, 16.f) {}

    void Buttons::render(double time) {
        this->_open.render(time);
        ImGui::SameLine();
        this->_erase.render(time);
    } 
}