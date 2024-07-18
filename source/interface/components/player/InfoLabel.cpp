#include "InfoLabel.hpp"

#include <imgui.h>

#include "../../../audio/MetaData.hpp"
#include "../../interfaces/Player.hpp"

namespace tock::interface::player {
    InfoLabel::InfoLabel(Player * parent)
    : Component(parent), _title("No Tracks Loaded."), _album(), _author("Please, give us a file to look at !"), _year() {
        this->_title.reserve(64);
        this->_album.reserve(64);
        this->_author.reserve(64);
        this->_year.reserve(64);
    }

    void InfoLabel::load(const audio::Sound & sound) {
        audio::MetaData data(sound);
        std::optional<FMOD_TAG> title = data.get({"TITLE", "TIT2"});
        std::optional<FMOD_TAG> album = data.get({"ALBUM", "TALB"});
        std::optional<FMOD_TAG> author = data.get({"ARTIST", "TPE1"});
        std::optional<FMOD_TAG> year = data.get({"YEAR", "TYER"});

        this->_title  =  title.has_value()  ? static_cast<char *>(title->data) : "Unknown Track";
        this->_album  =  album.has_value()  ? static_cast<char *>(album->data) : "";
        this->_author =  author.has_value() ? static_cast<char *>(author->data) : "Unknown Artist";
        this->_year   =  year.has_value()   ? static_cast<char *>(year->data) : "";
    }

    void InfoLabel::render(double time) {
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(8.f, 7.f));

        auto windowWidth = ImGui::GetWindowSize().x;
        auto textWidth = ImGui::CalcTextSize(this->_title.c_str()).x;

        ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
        ImGui::Text(this->_title.c_str());

        std::string subTible = this->_author;
        if(!this->_year.empty()) {
            subTible.append(" (" + this->_year + ")");
        }
            
        textWidth = ImGui::CalcTextSize(subTible.c_str()).x;
        ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
        ImGui::Text("%s", subTible.c_str());

        ImGui::PopStyleVar(1);
    }
}