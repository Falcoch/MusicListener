#include "EraseButton.hpp"

#include <tinyfiledialogs/tinyfiledialogs.h>
#include "../../interfaces/List.hpp"
#include "../../interfaces/Player.hpp"

#include <iostream>

namespace tock::interface::list {
    EraseButton::EraseButton(List * parent, float size) 
    : Button(parent, "##EraseButton", size, "assets/texture/button/minus.png") {}

    void EraseButton::onPressed(double) {
        std::optional<std::reference_wrapper<Element>> selected = this->parent()->selected();

        if(selected.has_value()) {
            std::cout << "Erase : " << selected->get().path() << std::endl;
        }
    }
}