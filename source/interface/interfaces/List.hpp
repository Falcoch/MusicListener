#pragma once

#include <GL/glew.h>
#include <vector>
#include <memory>

#include "Interface.hpp"
#include "../Renderer.hpp"

#include "../components/list/Titlebar.hpp"
#include "../components/list/Buttons.hpp"
#include "../components/list/Element.hpp"

#include "../../utils/Window.hpp"

namespace tock::interface {
    class Player;
    class List : public Interface<Renderer> {
        private:
            Player & _player;

            list::Titlebar _titlebar;
            list::Buttons _buttons;
            std::vector<std::unique_ptr<list::Element>> _elements;

        public:
            List(Renderer & manager, Player &);
           ~List();

            inline const utils::Window & window() {return this->parent()->window();}
            inline const Player & player() {return this->_player;}

            void play(list::Element &);
            void play(const std::filesystem::path &);

            void add(const std::filesystem::path &);
            void add(const audio::Sound &);

            void erase(const std::filesystem::path &);
            void erase(const audio::Sound &);

            const std::optional<std::reference_wrapper<list::Element>> selected() const;
            const std::optional<std::reference_wrapper<list::Element>> playing() const;

            void close();
            void unslectAll();

            void pause(bool);

            bool contain(const audio::Sound &) const;
            bool contain(const std::filesystem::path &) const;

            void render(double); 
            void update(double);
    };
}