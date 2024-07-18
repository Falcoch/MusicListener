#include "ParameterButton.hpp"

#include <iostream>

#include "../../interfaces/Player.hpp"

namespace tock::interface::player {
    ParameterButton::ParameterButton(Player * parent, float size)
    : Button(parent, "##ParameterButton", size, "assets/texture/button/parameter.png"),
      _parameter(nullptr) {}

    void ParameterButton::onPressed(double time) {
        Renderer & manager = *this->parent()->parent();
        this->_parameter.reset(nullptr);
        this->_parameter = std::make_unique<Parameter>(manager, this->parent()->window());
        manager.push(*this->_parameter.get());
    }
}