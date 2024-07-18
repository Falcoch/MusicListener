#pragma once 

#include <GL/glew.h>

#include "../Component.hpp"
#include "../../../utils/Texture.hpp"

namespace tock::interface {
    class Player;
}

namespace tock::interface::player {
    class PlayButton : public interface::Component<Player> {
        private:
            utils::Texture _icon;
            float _size;
            bool _playing;

        public:
            PlayButton() = delete;
            PlayButton(Player *, float = 64.f);
           ~PlayButton() = default;

            inline float size() const {return this->_size;}
            inline bool isPlaying() const {return this->_playing;}

            inline void setPlaying(bool state) {this->_playing = state;}

            virtual void render(double); 
    };
}