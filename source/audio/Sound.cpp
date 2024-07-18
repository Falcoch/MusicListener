#include "Sound.hpp"

#include "../error/FMod_Error.hpp"

#include <iostream>

namespace tock::audio {
    Sound::Sound(FMOD::Sound & sound)
    : _system(nullptr), _sound(&sound) {
        std::cerr << "Construct Sound" << std::endl;
        FMOD_RESULT result = FMOD_OK;
        result = sound.getSystemObject(&this->_system);
        error::FMod_Error::check(result);
    }

    Sound::Sound(FMOD::Channel & channel)
    : _system(nullptr), _sound(nullptr) {
        std::cerr << "Construct Sound" << std::endl;
        FMOD_RESULT result = FMOD_OK;
        result = channel.getSystemObject(&this->_system);
        error::FMod_Error::check(result);

        result = channel.getCurrentSound(&this->_sound);
        error::FMod_Error::check(result);
    }

    Sound::Sound(FMOD::System & system, const std::filesystem::path & path)
    : _system(&system), _sound(nullptr) {
        std::cerr << "Construct Sound : " << path << std::endl;
        if(!path.empty()) {
            this->load(path);
        }
    }

    Sound::Sound(const Sound & src) 
    : _system(src._system), _sound(nullptr) {
        std::cerr << "Construct Copy Sound" << src._path << std::endl;
        if(!src._path.empty()) {
            this->load(src._path);
        }
    }

    Sound Sound::operator=(const Sound & src) {
        std::cerr << "Construct operator= Sound" << src._path << std::endl;
        this->_system = src._system;
        this->_sound = nullptr;
        this->_path = src._path;

        if(!this->_path.empty()) {
            this->load(this->_path);
        }

        return *this;
    }

    Sound::~Sound() {
        std::cerr << "Destroy Sound : " << this->path() << std::endl;
        if(this->_sound != nullptr) {
            this->_sound->release();
        }
    }

    void Sound::load(const std::filesystem::path & path) {
        if(this->_sound != nullptr) {
            this->_sound->release();
        }

        if(std::filesystem::exists(path) && !std::filesystem::is_directory(path)) {
            FMOD_RESULT result = FMOD_OK;
            result = this->_system->createSound(path.string().c_str(), FMOD_DEFAULT, NULL, &this->_sound);
            error::FMod_Error::check(result);
            this->_path = path;
        }
    }

    std::string_view Sound::filename() const {
        char title[255] = {};
        this->_sound->getName(title, 255);
        return std::string_view(title);
    }

    unsigned int Sound::lenght() const {
        FMOD_RESULT result = FMOD_OK;
        unsigned int lenght = 0;
        result = this->_sound->getLength(&lenght, FMOD_TIMEUNIT_MS);
        error::FMod_Error::check(result);
        return lenght;
    }

    unsigned int Sound::size() const {
        FMOD_RESULT result = FMOD_OK;
        unsigned int size = 0;
        result = this->_sound->getLength(&size, FMOD_TIMEUNIT_RAWBYTES);
        error::FMod_Error::check(result);
        return size;
    }
}