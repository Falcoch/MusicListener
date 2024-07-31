#pragma once

#include "../Component.hpp"

namespace tock::interface {
    class List;
}

namespace tock::interface::list {
    class Header : public Component<List> {
        public:
            Header() = delete;
            Header(List *);
   virtual ~Header() = default;

            void render(double) override; 
    };
}