#include "MetaData.hpp"

#include "../error/FMod_Error.hpp"

namespace tock::audio {
    MetaData::MetaData(const Sound & sound) {
        this->read(sound);
    }

    MetaData::MetaData(FMOD::Sound * sound) {
        this->read(sound);
    }

    MetaData::MetaData(FMOD::System * system, const std::filesystem::path & path) {
        this->read(system, path);
    }

    void MetaData::read(const Sound & sound) {
        this->read(sound.address());
    }

    void MetaData::read(FMOD::System * system, const std::filesystem::path & path) {
        FMOD::Sound * sound = nullptr;
        FMOD_RESULT result = FMOD_OK;

        result = system->createSound(path.string().c_str(), FMOD_DEFAULT, NULL, &sound);
        error::FMod_Error::check(result);

        this->read(sound);
        sound->release();
    }

    void MetaData::read(FMOD::Sound * sound) {
        int tags, tagsUpdated;
        sound->getNumTags(&tags, &tagsUpdated);

        for(size_t i = 0; i < static_cast<size_t>(tags); i++) {
            FMOD_TAG tag;
            sound->getTag(nullptr, static_cast<int>(i), &tag);
            this->insert_or_assign(std::string(tag.name), tag);
        }
    }

    std::optional<FMOD_TAG> MetaData::get(std::string name) const {
        if(this->contains(name)) {
            return this->at(name);
        }
        return std::optional<FMOD_TAG>();
    }

    std::optional<FMOD_TAG> MetaData::get(const std::vector<std::string> & names) const {
        for(auto & name : names) {
            std::optional<FMOD_TAG> tag = this->get(name);
            if(tag.has_value()) {
                return tag;
            }
        }
        return std::optional<FMOD_TAG>();
    }
}