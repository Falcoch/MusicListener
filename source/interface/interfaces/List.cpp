#include "List.hpp"

#include <imgui.h>
#include <iostream>

#include "Player.hpp"

namespace tock::interface {
    List::List(Renderer & manager, Player & player) 
    : Interface(manager), 
      _player(player),
      _titlebar(this),
      _buttons(this),
      _header(this) {
        std::cout << "Construct List Interface" << std::endl;
         int width = 0, height = 0, channels = 4;
        unsigned char * data = stbi_load("assets/texture/button/line.png", &width, &height, &channels, 0);
        this->_decoration.store(width, height, data, channels == 4 ? utils::Texture::RGBA : utils::Texture::RGB);
        stbi_image_free(data);
    }

    List::~List() {
        std::cout << "Destruct List Interface" << std::endl;
    }

    void List::play(list::Element & element) {
        std::filesystem::path path = element.path();

        if(!std::filesystem::exists(path) || std::filesystem::is_directory(path)) {
            throw std::runtime_error("Can't load file : " + path.string());
        }

        this->_player.load(path.string());
        this->_player.play();

        this->unslectAll();
        element.setSelected(true);
    }

    void List::play(const audio::Sound & sound) {
        std::optional<std::reference_wrapper<list::Element>> exist = this->find(sound);
        if(exist.has_value()) {
            this->play(exist.value());
            return;
        }

        std::unique_ptr<list::Element> element = std::make_unique<list::Element>(this, sound.path());
        this->play(*element.get());
        this->_elements.push_back(std::move(element));
    }

    void List::play(const std::filesystem::path & path) {
        for(auto & element : this->_elements) {
            if(element->path() == path) {
                this->play(*element.get());
                return;
            }
        }

        std::unique_ptr<list::Element> element = std::make_unique<list::Element>(this, path);
        this->play(*element.get());

        this->_elements.push_back(std::move(element));
    }

    void List::add(const std::filesystem::path & path) {
        if(!std::filesystem::exists(path) || std::filesystem::is_directory(path)) {
            throw std::runtime_error("Can't load file : " + path.string());
        }

        std::unique_ptr<list::Element> element = std::make_unique<list::Element>(this, path);
        this->_elements.push_back(std::move(element));
    }

    void List::add(const audio::Sound & sound) {
        if(sound.isUsable()) {
            this->add(sound.path());
        }
    }

    void List::erase(const std::filesystem::path & path) {
        if(!this->contain(path)) {
            return;
        }

        for(auto it = this->_elements.begin(); it != this->_elements.end();) {
            if(it->get()->path() == path) {
                it = this->_elements.erase(it);
            }
            else {
                ++it;
            }
        }
    }

    void List::erase(const audio::Sound & sound) {
        if(sound.isUsable()) {
            this->erase(sound.path());
        }
    }

    const std::optional<std::reference_wrapper<list::Element>> List::selected() const {
        for(auto & element : this->_elements) {
            if(element->isSelected()) {
                return std::optional<std::reference_wrapper<list::Element>>(*element.get());
            }
        }
        return std::optional<std::reference_wrapper<list::Element>>();
    }

    const std::optional<std::reference_wrapper<list::Element>> List::playing() const {
        audio::Sound * played = this->_player.currentTrack();

        if(played == nullptr) {
            return std::optional<std::reference_wrapper<list::Element>>();
        }

        for(auto & element : this->_elements) {
            if(element->path() == played->path()) {
                return std::optional<std::reference_wrapper<list::Element>>(*element);
            }
        }

        return std::optional<std::reference_wrapper<list::Element>>();
    }

    void List::close() {
        this->parent()->fall(*this);
    }

    void List::unslectAll() {
        for(auto & element : this->_elements) {
            element->setSelected(false);
        }
    }

    void List::pause(bool state) {
        this->_player.pause(state);
    }

    bool List::contain(const audio::Sound & sound) const {
        return this->contain(sound.path());
    }

    bool List::contain(const std::filesystem::path & path) const {
        for(auto & element : this->_elements) {
            if(element->path().string() == path.string()) {
                return true;
            }
        }
        return false;
    }

    std::optional<std::reference_wrapper<list::Element>> List::find(const audio::Sound & sound) const {
        for(auto & element : this->_elements) {
            if(*element.get() == sound) {
                return std::optional<std::reference_wrapper<list::Element>>(*element.get());
            }
        }
        return std::optional<std::reference_wrapper<list::Element>>();
    }

    std::optional<std::reference_wrapper<list::Element>> List::find(const std::filesystem::path & path) const {
        for(auto & element : this->_elements) {
            if(element->path() == path) {
                return std::optional<std::reference_wrapper<list::Element>>(*element.get());
            }
        }
        return std::optional<std::reference_wrapper<list::Element>>();
    }

    void List::render(double time) {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.f, 0.f));

        if(ImGui::Begin("##List", NULL, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysUseWindowPadding)) {
            ImGui::BeginChild(ImGui::GetID("Title"), ImVec2(ImGui::GetWindowWidth(), this->_titlebar.height()));
            this->_titlebar.render(time);
            ImGui::EndChild();

            ImGui::BeginChild("List", ImVec2(0, 0), 0, ImGuiWindowFlags_AlwaysVerticalScrollbar);

            this->_buttons.render(time);
            this->_header.render(time);

            ImGui::Image((void*)(intptr_t)this->_decoration.identifier(), ImVec2(ImGui::GetWindowWidth(), 32.f));

            if(!this->_elements.empty()) {
                int id = 0;
                for(auto & element : this->_elements) {
                    ImGui::PushID(id);
                    element->render(time);
                    ++id;
                    ImGui::PopID();
                }
            }
            else {
                static std::string text = "No Tracks Loaded";
                static float text_size = ImGui::CalcTextSize(text.c_str()).x;

                ImGui::SetCursorPos(ImVec2(ImGui::GetWindowWidth()/2.f - text_size/2.f, ImGui::GetCursorPosY()));

                ImGui::Text(text.c_str());
            }

            ImGui::EndChild();
        }
        ImGui::End();

        ImGui::PopStyleVar(2);
    }

    void List::update(double) {
        audio::Sound * current = this->_player.currentTrack();
        
        if(current != nullptr) {
            if(!this->contain(*current)) {
                std::unique_ptr<list::Element> element = std::make_unique<list::Element>(this, current->path());
                this->_elements.push_back(std::move(element));
            }
        }
    }
}