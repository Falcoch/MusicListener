#pragma once

#include <GL/glew.h>
#include "../Component.hpp"

#include "../../../utils/Texture.hpp"
#include "../../../audio/Sound.hpp"

namespace tock::interface {
    class Player;
}

namespace tock::interface::player {
    class Icon : public Component<Player> {
        private:
            std::unique_ptr<utils::Texture> _icon;
            utils::Texture _overlay;
            utils::Texture _paused;
            std::string _defaultMessage;

        public:
            Icon() = delete;
            Icon(Player *, const std::string & defaultMessage);
   virtual ~Icon() = default;

            void load(const audio::Sound &);
            void unload();
            virtual void render(double);
    };
}