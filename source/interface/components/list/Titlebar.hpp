#pragma once

#include "../Component.hpp"

namespace tock::interface {
    class List;
}

namespace tock::interface::list {
    class Titlebar : public interface::Component<List> {
        private:
            float _height;

        public: 
            Titlebar(List *, float = 24.f);
   virtual ~Titlebar() = default;

            inline float height() const {return this->_height;}

            void render(double) override;
    };
}