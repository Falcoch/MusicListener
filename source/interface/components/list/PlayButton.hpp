#pragma once

#include "../Component.hpp"

#include <filesystem>
#include "../../../utils/Texture.hpp"

namespace tock::interface {
    class List;
    class Player;
}

namespace tock::interface::list {
    class PlayButton : public interface::Component<List> {
        private:
            utils::Texture _icon;
            std::filesystem::path _path;
            float _size;

        public:
            PlayButton(List *, float, const std::filesystem::path &);
   virtual ~PlayButton() = default;

            virtual void render(double); 

            inline const std::filesystem::path & path() const {return this->_path;}
            inline float size() const {return this->_size;}

            inline void setSize(float size) {this->_size = size;}
    };
}