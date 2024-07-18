#pragma once

#include <GL/glew.h>

#include "../../Button.hpp"

#include <memory>
#include "../../interfaces/Parameter.hpp"

namespace tock::interface {
    class Player;
}

namespace tock::interface::player {
    class ParameterButton : public interface::Button<Player> {
        private:
            std::unique_ptr<Parameter> _parameter;

        public:
            ParameterButton(Player *, float);
   virtual ~ParameterButton() = default;

            void onPressed(double) override;
    };
}