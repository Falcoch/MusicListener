#include "ListButton.hpp"

#include <iostream>

#include "../../interfaces/Player.hpp"

namespace tock::interface::player {
    ListButton::ListButton(Player * parent, float size)
    : Button(parent, "##ListButton", size, "assets/texture/button/list.png"), _list(nullptr), _displayed(false) {
        Renderer & manager = *this->parent()->parent();
        this->_list = std::make_unique<List>(manager, *this->parent());
        manager.subscribe(*this->_list);
    }

    ListButton::~ListButton() {
        Renderer & manager = *this->parent()->parent();
        manager.unsubscribe(*this->_list);
    }

    void ListButton::onPressed(double time) {
        Renderer & manager = *this->parent()->parent();
        if(!this->_displayed) {
            manager.push(*this->_list.get());
        }   
    }
}