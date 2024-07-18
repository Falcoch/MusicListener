#pragma once

#include <GL/glew.h>
#include "../Component.hpp"

#include <memory>
#include <vector>

namespace tock::interface {
    class Player;
}

namespace tock::interface::player {
    class Titlebar : public interface::Component<Player> {
        private:
            float _height;
            
        public: 
            Titlebar() = delete;
            Titlebar(Player *, float = 24.f);
   virtual ~Titlebar() = default;

            inline float height() const {return this->_height;}

            void render(double) override;
    };
}