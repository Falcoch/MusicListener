#pragma once

#include <exception>

#include "../include/fmod/fmod.h"
#include "../include/fmod/fmod_errors.h" 

namespace tock::error {
    class FMod_Error : public std::exception {
        private:
            FMOD_RESULT _code;

        public:
            FMod_Error() = delete;
            FMod_Error(FMOD_RESULT code);
           ~FMod_Error() = default;

            const char * what() const noexcept override;

            static void check(FMOD_RESULT code, bool = true);
    };   
}