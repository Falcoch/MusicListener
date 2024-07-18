#pragma once

#include "../Component.hpp"

namespace tock::interface {
    class Parameter;
}

namespace tock::interface::parameter {
    class Titlebar : public interface::Component<Parameter> {
        private:
            float _height;

        public: 
            Titlebar(Parameter *, float = 24.f);
   virtual ~Titlebar() = default;

            void render(double) override;
    };
}