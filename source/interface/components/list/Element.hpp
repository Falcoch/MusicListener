#pragma once

#include "../Component.hpp"

namespace tock::interface {
    class List;
}

#include <string>

#include "../../../audio/Sound.hpp"
#include "../../../utils/Texture.hpp"

#include "PlayButton.hpp"

namespace tock::interface::list {
    class Element : public Component<List> {
        private:
            std::filesystem::path _path;
            std::string _title;
            std::string _artist;
            std::string _year;
            bool _selected;
            bool _hovered;

            PlayButton _button;

        public:
            Element() = delete;
            Element(List *, const std::filesystem::path & = "");
            Element(const Element &);
   virtual ~Element() = default;

            void render(double) override;
            void load(const std::filesystem::path &);

            inline const std::filesystem::path & path() const {return this->_path;}
            inline const std::string & title() const {return this->_title;}
            inline const std::string & artist() const {return this->_artist;}
            inline const std::string & year() const {return this->_year;}

            inline bool isSelected() const {return this->_selected;}   
            inline bool isHovered() const {return this->_hovered;}

            const PlayButton & getPlayButton() const {return this->_button;}

            inline void setSelected(bool state) {this->_selected = state;}

            inline friend bool operator==(const Element & a, const Element & b) {return a._path == b._path;}
            inline friend bool operator!=(const Element & a, const Element & b) {return !(a == b);}
    };
}