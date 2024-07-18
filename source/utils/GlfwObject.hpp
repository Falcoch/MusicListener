#pragma once

namespace tock::utils {
    class GlfwObject {
        private:
            static bool _Initilized;

        public:
            GlfwObject();
           ~GlfwObject() = default;

            inline static bool isInitilized() {return GlfwObject::_Initilized;}
    };
}