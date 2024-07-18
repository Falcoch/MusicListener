#include "List.hpp"

#include <imgui.h>
#include <iostream>

#include "Player.hpp"

namespace tock::interface {
    List::List(Renderer & manager, Player & player) 
    : Interface(manager), 
      _player(player),
      _titlebar(this),
      _buttons(this) {
        std::cout << "Construct List Interface" << std::endl;
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

    void List::render(double time) {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.f, 0.f));

        if(ImGui::Begin("##List", NULL, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysUseWindowPadding)) {
            ImGui::BeginChild(ImGui::GetID("Title"), ImVec2(ImGui::GetWindowWidth(), this->_titlebar.height()));
            this->_titlebar.render(time);
            ImGui::EndChild();

            ImGui::BeginChild("List", ImVec2(0, 0), 0, ImGuiWindowFlags_AlwaysVerticalScrollbar);

            this->_buttons.render(time);

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
                ImGui::Text("No Tracks Loaded");
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