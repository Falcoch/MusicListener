#pragma once

#include <memory>

#include "../include/fmod/fmod_studio.h"
#include "../include/fmod/fmod_studio.hpp"
#include "../include/fmod/fmod.h"

#include "Sound.hpp"

namespace tock::audio {
    class Player {
        public:
            enum Status : uint8_t {
                EMPTY,
                READY,
                PLAYING,
                PAUSING,
                COMPLET,
            };

        private:
            FMOD::System * _system;
            FMOD::Channel * _channel;
            Sound * _current;
            Status _status;
            bool _looping;

        public:
            Player();
            Player(Sound &);
           ~Player();

            inline FMOD::System * system() const {return this->_system;}
            inline Sound * current() const {return this->_current;} 
            inline bool isLooping() const {return this->_looping;}

            inline void setLooping(bool state) {this->_looping = state;}

            unsigned int getPosition() const;
            float getVolume() const;

            void setPosition(unsigned int);
            void setVolume(float);

            void load(Sound &);
            void reload();
            void unload();

            void play();
            void pause();
            void stop();

            void update();

            inline bool isEmpty() const {return this->_status == EMPTY;}
            inline bool isReady() const {return this->_status == READY;}
            inline bool isPlaying() const {return this->_status == PLAYING;}
            inline bool isPausing() const {return this->_status == PAUSING;}
            inline bool isComplet() const {return this->_status == COMPLET;}

            inline Status getStatus() const {return this->_status;}
    };
}