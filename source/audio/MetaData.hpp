#pragma once

#include <map>
#include <string>
#include <vector>

#include "Sound.hpp"

namespace tock::audio {
    class MetaData : public std::map<std::string, FMOD_TAG> {
        public:
            MetaData() = default;
            MetaData(const Sound &);
            MetaData(FMOD::Sound *);
            MetaData(FMOD::System *, const std::filesystem::path &);
           ~MetaData() = default;

            void read(const Sound &);
            void read(FMOD::System *, const std::filesystem::path &);
            void read(FMOD::Sound *);
            
            std::optional<FMOD_TAG> get(std::string) const;
            std::optional<FMOD_TAG> get(const std::vector<std::string> &) const;
            inline std::optional<FMOD_TAG> get(const std::initializer_list<std::string> & names) const {return this->get(std::vector<std::string>(names));}
    };
}