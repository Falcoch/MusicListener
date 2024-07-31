#include "Element.hpp"

#include <imgui.h>
#include "../../interfaces/Player.hpp"
#include "../../../audio/MetaData.hpp"
#include "../../../../include/stb/stb_image.h"

#include <iostream>

namespace tock::interface::list {
    Element::Element(List * parent, const std::filesystem::path & path) 
    : Component<List>(parent), 
      _path(path),
      _title("Unknown Track"),
      _artist("Unknwow Artist"),
      _year(""),
      _selected(false),
      _hovered(false),
      _button(parent, 0.f, path) {
        float heightOffset = ImGui::CalcTextSize("@").y;
        float buttonSize = heightOffset * 4.f;

        this->_button.setSize(buttonSize/3.f);

        this->load(path);
    }

    void Element::load(const std::filesystem::path & path) {
        if(!std::filesystem::exists(path) || std::filesystem::is_directory(path)) {
            return;
        }

        audio::MetaData data(this->parent()->player().system(), path);
        if(data.empty()) {
            return;
        }

        this->_path = path;

        std::optional<FMOD_TAG> title = data.get({"TITLE", "TIT2"});
        std::optional<FMOD_TAG> author = data.get({"ARTIST", "TPE1"});
        std::optional<FMOD_TAG> year = data.get({"YEAR", "TYER"});

        this->_title  =  title.has_value()  ? static_cast<char *>(title->data) : "Unknown Track";
        this->_artist =  author.has_value() ? static_cast<char *>(author->data) : "Unknown Artist";
        this->_year   =  year.has_value()   ? static_cast<char *>(year->data) : "";
    }

    void Element::render(double time) {
        ImVec2 size = ImGui::GetWindowSize();

        float buttonSize =  ImGui::CalcTextSize("@").y * 4.f;

        ImVec4 bgColor = ImGui::GetStyleColorVec4(ImGuiCol_ChildBg);

        if(this->_selected) {
            bgColor = ImGui::GetStyleColorVec4(ImGuiCol_Button);
        }
        else if(this->_hovered) {
            bgColor = ImGui::GetStyleColorVec4(ImGuiCol_Button);
            bgColor.x *= 1.25f;
            bgColor.y *= 1.25f;
            bgColor.z *= 1.25f;
        }

        ImGui::PushStyleColor(ImGuiCol_ChildBg, bgColor);
        ImGui::BeginChild("##Element", ImVec2(ImGui::GetWindowWidth(), buttonSize), 0, 0);
        ImGui::Columns(2, "#Element", false);

        {
            float collumnWidth = ImGui::GetWindowWidth() - buttonSize;
            ImGui::SetColumnWidth(ImGui::GetColumnIndex(), collumnWidth);
            ImGui::PushStyleColor(ImGuiCol_Button, this->_selected ? ImGui::GetStyleColorVec4(ImGuiCol_Button) : ImGui::GetStyleColorVec4(ImGuiCol_WindowBg));

            std::string title = "   " + this->_title;
            std::string artist = "   " + this->_artist;

            ImGui::Text("");
            ImGui::Text(title.c_str());
            ImGui::Text(artist.c_str());

            if(!this->_year.empty()) {
                ImGui::SameLine();
                std::string year = " (" + this->_year + ")";
                ImGui::Text(year.c_str());
            }

            ImGui::PopStyleColor(1);
        }

        ImGui::NextColumn();

        {
            ImGui::SetColumnWidth(ImGui::GetColumnIndex(), buttonSize);

            ImGui::Text("");
            this->_button.render(time);
            ImGui::Text("");
        }

        ImGui::Columns();
        ImGui::EndChild();

        if(ImGui::IsItemClicked(ImGuiMouseButton_Left)) {
            if(this->_selected) {
                this->parent()->pause(this->parent()->player().isPaused());
            }
            else {
                this->parent()->unslectAll();
                this->_selected = true;
            }
        }
        this->_hovered = ImGui::IsItemHovered();

        ImGui::PopStyleColor(1);
    }
}