#pragma once

#include <GL/glew.h>
#include "../Component.hpp"

namespace tock::interface {
    class Player;
}

namespace tock::interface::player {
    class TimeSlider : public interface::Component<Player> {
        private:
            int _value;
            bool _modify;
            
        public:
            TimeSlider() = delete;
            TimeSlider(Player *);
           ~TimeSlider() = default;

            virtual void render(double); 
    };
}