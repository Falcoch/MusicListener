#pragma once

#include <string>
#include <filesystem>
#include <optional>

#include "../include/fmod/fmod_studio.h"
#include "../include/fmod/fmod_studio.hpp"
#include "../include/fmod/fmod.h"

namespace tock::audio {
    class Sound {
        private:
            FMOD::System * _system;
            FMOD::Sound * _sound;
            std::filesystem::path _path;

        public:
            Sound() = delete;
            Sound(FMOD::Sound &);
            Sound(FMOD::Channel &);
            Sound(FMOD::System &, const std::filesystem::path &);
            Sound(const Sound &);
            Sound(const Sound &&) = delete;
            Sound operator=(const Sound &);
            Sound operator=(const Sound &&) = delete;
           ~Sound();

            inline FMOD::System * system() const {return this->_system;}
            inline FMOD::Sound * address() const {return this->_sound;} 
            inline std::filesystem::path path() const {return this->_path;} 

            inline bool isUsable() const {return this->_system != nullptr && this->_sound != nullptr && !this->_path.empty();}

            std::string_view filename() const;

            unsigned int lenght() const;
            unsigned int size() const;

            void load(const std::filesystem::path &);

            inline friend bool operator==(const Sound & a, const Sound & b) {return (!b.isUsable() || !a.isUsable()) && b._path == a._path;}
            inline friend bool operator!=(const Sound & a, const Sound & b) {return !(b == a);}
    };
}