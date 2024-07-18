#include "Player.hpp"

#include "../error/FMod_Error.hpp"

#include <iostream>

namespace tock::audio {
    Player::Player() 
    : _system(nullptr), _channel(nullptr), _current(nullptr), _status(EMPTY), _looping(true) {
        std::cerr << "Construct Player" << std::endl;
        FMOD_RESULT result = FMOD_OK;
        result = FMOD::System_Create(&this->_system); 
        error::FMod_Error::check(result);

        result = this->_system->init(512, FMOD_INIT_NORMAL, NULL);
        error::FMod_Error::check(result);
    }

    Player::Player(Sound & sound) 
    : Player()  {
        std::cerr << "Construct Player" << std::endl;
        this->load(sound);
    }

    Player::~Player() {
        std::cerr << "Destroy Player" << std::endl;
        FMOD_RESULT result = FMOD_OK;
        result = this->_system->close();
        error::FMod_Error::check(result);

        result = this->_system->release();
        error::FMod_Error::check(result);
    }

    unsigned int Player::getPosition() const {
        unsigned int position = 0;
        if(!this->isEmpty()) {
            FMOD_RESULT result = FMOD_OK;
            result = this->_channel->getPosition(&position, FMOD_TIMEUNIT_MS);
            error::FMod_Error::check(result);
        }
        return position;
    }

    void Player::setPosition(unsigned int position) {
        if(!this->isEmpty()) {
            FMOD_RESULT result = FMOD_OK;

            unsigned int lenght = this->_current->lenght();
            result = this->_channel->setPosition(position >= lenght ? lenght : position, FMOD_TIMEUNIT_MS);
            error::FMod_Error::check(result);
        }
    }

    float Player::getVolume() const {
        float volume = 0;
        if(!this->isEmpty()) {
            FMOD_RESULT result = FMOD_OK;
            result = this->_channel->getVolume(&volume);
            error::FMod_Error::check(result);
        }
        return volume;
    }

    void Player::setVolume(float volume) {
        if(!this->isEmpty()) {
            FMOD_RESULT result = FMOD_OK;
            result = this->_channel->setVolume(volume);
            error::FMod_Error::check(result);
        }
    }

    void Player::load(Sound & sound) { 
        FMOD_RESULT result = FMOD_OK;
        result = this->_system->playSound(sound.address(), NULL, false, &this->_channel);
        error::FMod_Error::check(result);
        this->_current = &sound;

        result = this->_channel->setPaused(true);
        error::FMod_Error::check(result);

        this->_status = READY;
    }

    void Player::reload() {
        if(!this->isEmpty()) {
            this->unload();
            this->load(*this->_current);
        }
    }

    void Player::unload() {
        if(!this->isEmpty()) {
            this->_channel->stop();
            this->_channel = nullptr;
            this->_current = nullptr;

            this->_status = EMPTY;
        }
    }

    void Player::play() {
        if(this->_current != nullptr) {
            FMOD_RESULT result = FMOD_OK;
            result = this->_channel->setPaused(false);
            error::FMod_Error::check(result);

            this->_status = PLAYING;
        }
    }

    void Player::pause() {
        if(this->_current != nullptr) {
            FMOD_RESULT result = FMOD_OK;
            result = this->_channel->setPaused(!this->isPausing());
            error::FMod_Error::check(result);

            this->_status = PAUSING;
        }
    }

    void Player::stop() {
        if(this->_current != nullptr) {
            this->pause();
            this->setPosition(0);

            this->_status = READY;
        }
    }

    void Player::update() {
        if(!this->isEmpty() && !this->isComplet()) {
            FMOD_RESULT result = FMOD_OK;
            bool playing;
            result = this->_channel->isPlaying(&playing);
            error::FMod_Error::check(result);
            
            if(playing) {
                result = this->_system->update();
                error::FMod_Error::check(result);
            }
            else {
                this->_status = COMPLET;
            }

            if(this->_looping && this->isComplet()) {
                this->setPosition(0);
                this->_status = PLAYING;
            }
        }
    }
}