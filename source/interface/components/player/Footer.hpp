#pragma once

#include <GL/glew.h>

#include "../Component.hpp"

namespace tock::interface {
    class Player;
}

namespace tock::interface::player {
    class Footer : public Component<Player> {
        private:
            float _height;

        public: 
            Footer() = delete;
            Footer(Player *, float = 20.f);
   virtual ~Footer() = default;

            inline float height() const {return this->_height;}

            void render(double) override;
    };
}