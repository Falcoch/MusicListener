#pragma once

#include <GL/glew.h>

#include "Interface.hpp"
#include "../Renderer.hpp"

#include "../components/player/Icon.hpp"
#include "../components/player/InfoLabel.hpp"
#include "../components/player/TimeSlider.hpp"
#include "../components/player/Titlebar.hpp"
#include "../components/player/Buttons.hpp"
#include "../components/player/Footer.hpp"

#include "../../utils/Window.hpp"
#include "../../audio/Player.hpp"

namespace tock::interface {
    class Player : public Interface<Renderer> {
        private:
            std::unique_ptr<audio::Sound> _currentTrack;
            audio::Player & _player;

            player::Titlebar _titlebar;
            player::Icon _icon;
            player::InfoLabel _label;
            player::TimeSlider _slider;
            player::Buttons _button;
            player::Footer _footer;

        public:
            Player() = delete;
            Player(Renderer &, audio::Player &);
           ~Player();

            inline audio::Sound * currentTrack() const {return this->_currentTrack.get();}

            inline const audio::Player & player() const {return this->_player;}
            inline const utils::Window & window() const {return this->parent()->window();}
            inline FMOD::System * system() const {return this->_player.system();}

            void load();
            void load(audio::Sound &);
            void load(const std::filesystem::path &);
            void unload();

            void play();
            void play(audio::Sound &);
            void play(const std::filesystem::path &);
            
            void pause(bool);
            inline bool isPaused() const {return this->_player.isPausing();}

            void changeVolume(float);
            void changePosition(unsigned int);

            void render(double) override;   
            void update(double) override;      
    };
}