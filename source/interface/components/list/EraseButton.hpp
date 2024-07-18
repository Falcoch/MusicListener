#pragma once

namespace tock::interface {
    class List;
}

#include "../../Button.hpp"

namespace tock::interface::list {
    class EraseButton : public Button<List> {
        public:
            EraseButton(List *, float = 24.f);
   virtual ~EraseButton() = default;

            void onPressed(double) override;
    };
}