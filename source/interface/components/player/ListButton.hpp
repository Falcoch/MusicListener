#pragma once

#include <GL/glew.h>

#include "../../interfaces/List.hpp"
#include "../../Button.hpp"

#include <memory>

namespace tock::interface {
    class Player;
}

namespace tock::interface::player {
    class ListButton : public interface::Button<Player> {
        private:
            std::unique_ptr<List> _list;
            bool _displayed;

        public:
            ListButton(Player *, float);
   virtual ~ListButton();

            void onPressed(double) override;
    };
}