#pragma once

#include "../Component.hpp"

namespace tock::interface {
    class List;
}

#include "OpenButton.hpp"
#include "EraseButton.hpp"

namespace tock::interface::list {
    class Buttons : public Component<List> {
        private:
            OpenButton _open;
            EraseButton _erase;

        public:
            Buttons(List *);
   virtual ~Buttons() = default;

            void render(double) override;
        
    };
}