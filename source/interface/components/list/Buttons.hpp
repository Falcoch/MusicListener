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
            utils::Texture _decoration;
            OpenButton _open;
            EraseButton _erase;
            

        public:
            Buttons() = delete;
            Buttons(List *);
   virtual ~Buttons() = default;

            void render(double) override;
        
    };
}