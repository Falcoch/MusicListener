#include "PlayButton.hpp"

#include <imgui.h>

#include "../../../../include/stb/stb_image.h"

#include "../../interfaces/Player.hpp"

#include <iostream>

namespace tock::interface::player {
    PlayButton::PlayButton(Player * parent, float size)
    : Component(parent), _size(size), _playing(false) {
        int width = 0, height = 0, channels = 4;
        unsigned char * data = stbi_load("assets/texture/button/pause_play.png", &width, &height, &channels, 0);
        this->_icon.store(width, height, data, channels == 4 ? utils::Texture::RGBA : utils::Texture::RGB);
        stbi_image_free(data);
    }

    void PlayButton::render(double time) {
        static float offset = (this->parent()->window().width()-(this->_size/2.f))/2.1f;

        ImVec2 uv0 = !this->_playing ? ImVec2(0.5f, 0.0f) : ImVec2(0.0f, 0.0f);
        ImVec2 uv1 = !this->_playing ? ImVec2(1.0f, 1.0f) : ImVec2(0.5f, 1.0f);
        if(ImGui::ImageButton((void*)(intptr_t)this->_icon.identifier(), ImVec2(this->_size, this->_size), uv0, uv1)) {
            if(this->parent()->currentTrack() != nullptr) {
                this->_playing = !this->_playing;
                this->parent()->pause(!this->_playing);
            }
        }
    }
}