#include "PlayButton.hpp"

#include "../../interfaces/List.hpp"
#include "../../interfaces/Player.hpp"

#include <iostream>

namespace tock::interface::list {
    PlayButton::PlayButton(List * parent, float size, const std::filesystem::path & path)
    : Component(parent), _icon(), _path(path), _size(size) {
        int width = 0, height = 0, channels = 4;
        unsigned char * data = stbi_load("assets/texture/button/big_pause_play.png", &width, &height, &channels, 0);
        this->_icon.store(width, height, data, channels == 4 ? utils::Texture::RGBA : utils::Texture::RGB);
        stbi_image_free(data);
    }

    void PlayButton::render(double) {
        audio::Sound * current = this->parent()->player().currentTrack();

        bool isCurrent = current != nullptr && current->path() == this->_path.string();
        bool isPausing = this->parent()->player().player().isPausing();

        ImVec2 uv0 = isCurrent && !isPausing ? ImVec2(0.0f, 0.0f) : ImVec2(0.5f, 0.0f);
        ImVec2 uv1 = isCurrent && !isPausing ? ImVec2(0.5f, 1.0f) : ImVec2(1.0f, 1.0f);
        
        if(ImGui::ImageButton((void*)(intptr_t)this->_icon.identifier(), ImVec2(this->_size, this->_size), uv0, uv1)) {
            if(!isCurrent) {
                this->parent()->play(this->_path);
            }
            else {
                this->parent()->pause(!isPausing);
            }
        }
    }
}