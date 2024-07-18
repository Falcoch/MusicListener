#include "Player.hpp"

#include <imgui.h>
#include <tinyfiledialogs/tinyfiledialogs.h>

#include "../../../include/stb/stb_image.h"

#include <iostream>

namespace tock::interface {
    Player::Player(Renderer & parent, audio::Player & player) 
    : Interface(parent),
      _currentTrack(nullptr),
      _player(player),
      _titlebar(this),
      _icon(this, "You can give us a file by dragging it there !"),
      _label(this),
      _slider(this),
      _button(this, parent.window().width()/24.f),
      _footer(this) {
        std::cerr << "Construct Player Interface" << std::endl;
        std::optional<GLFWwindow *> address = parent.window().address();

        if(address.has_value()) {
            glfwSetWindowUserPointer(address.value(), static_cast<void *>(this));
            glfwSetDropCallback(address.value(), [](GLFWwindow * window, int count, const char ** paths) {
                Player * interface = reinterpret_cast<Player *>(glfwGetWindowUserPointer(window));
                if(count > 0) {
                    interface->load(std::string(paths[0]));
                }
            });
        }
    }

    Player::~Player() {
        std::cerr << "Destroy Player Interface" << std::endl;
        this->_player.stop();
    }

    void Player::load() {
        const char * filePattern[4] = {"*.mp3", "*.ogg", "*.wav", "*.flac"};
        const char * path = tinyfd_openFileDialog("Music Player", "./", 4, filePattern, "Audio Files", false);
        if(path != NULL) {
            this->load(std::string(path));
        }
    }

    void Player::load(audio::Sound & sound) {
        this->_player.load(sound);
        this->_icon.load(sound);
        this->_label.load(sound);
    }

    void Player::load(const std::filesystem::path & path) {
        bool shouldPlay = !this->_player.isPausing() || this->_currentTrack == nullptr;
        this->_player.stop();
        this->_currentTrack.reset(nullptr);
        this->_currentTrack = std::make_unique<audio::Sound>(*this->_player.system(), path.c_str());
        this->load(*this->_currentTrack);
        if(shouldPlay) {
            this->play();
        }
    }

    void Player::unload() {
        this->_player.unload();
        this->_button.setPlaying(false);
    }

    void Player::play() {
        this->_player.play();
        this->_button.setPlaying(true);
    }

    void Player::play(audio::Sound & file) {
        this->load(file);
        this->play();
    }

    void Player::play(const std::filesystem::path & path) {
        this->load(path);
        this->play();
    }

    void Player::pause(bool state) {
        if(state) {
            this->_player.pause();
        }
        else {
            this->_player.play();
        }
        
        this->_button.setPlaying(!state);
    }

    void Player::changeVolume(float volume) {
        this->_player.setVolume(volume);
    }

    void Player::changePosition(unsigned int position) {
        this->_player.setPosition(position);
    }

    void Player::render(double time) {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.f, 0.f));

        if(ImGui::Begin("##Player", NULL, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize)) {
            this->_titlebar.render(time);
            this->_icon.render(time);
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.f, 8.f));
            this->_slider.render(time);
            ImGui::PopStyleVar();
            this->_label.render(time);
            this->_button.render(time);
            this->_footer.render(time);
        }
        ImGui::End();

        ImGui::PopStyleVar(2);
    }

    void Player::update(double) {
        this->_player.update();
    }
}