#pragma once 

#include <GL/glew.h>
#include "../Component.hpp"

#include <string>
#include "../../../audio/Sound.hpp"

namespace tock::interface {
    class Player;
}

namespace tock::interface::player {
    class InfoLabel : public interface::Component<Player> {
        private:
            std::string _title, _album, _author, _year;

        public:
            InfoLabel() = delete;
            InfoLabel(Player *);
   virtual ~InfoLabel() = default;

            void load(const audio::Sound &);
            virtual void render(double); 
    };
}