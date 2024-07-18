#pragma once

namespace tock::interface {
    class List;
}

#include "../../Button.hpp"

namespace tock::interface::list {
    class OpenButton : public Button<List> {
        public:
            OpenButton(List *, float = 24.f);
   virtual ~OpenButton() = default;

            void onPressed(double) override;
    };
}