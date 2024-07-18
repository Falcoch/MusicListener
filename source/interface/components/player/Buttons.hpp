#pragma once 

#include <GL/glew.h>

#include "../Component.hpp"
#include "../../../utils/Texture.hpp"

#include "PlayButton.hpp"
#include "ParameterButton.hpp"
#include "ListButton.hpp"

namespace tock::interface {
    class Player;
}

namespace tock::interface::player {
    class Buttons : public interface::Component<Player> {
        private:
            utils::Texture _decoration;
            PlayButton _playButton;
            ParameterButton _parameterButton;
            ListButton _listButton;
            float _size;

        public:
            Buttons() = delete;
            Buttons(Player *, float = 32.f);
           ~Buttons() = default;

           inline const utils::Texture & getDecorations() const {return this->_decoration;}
           inline const PlayButton & getPlayButton() const {return this->_playButton;}
           inline const ParameterButton & getParameterButton() const {return this->_parameterButton;}
           inline const ListButton & getListButton() const {return this->_listButton;}

           inline float size() const {return this->_size;}

            void setPlaying(bool);

            virtual void render(double); 
    };
}