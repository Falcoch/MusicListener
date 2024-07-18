#include "FMod_Error.hpp"

#include <string>
#include <iostream>

namespace tock::error {
    FMod_Error::FMod_Error(FMOD_RESULT result)
    : _code(result) {}

    const char * FMod_Error::what() const noexcept {
        std::string message = "FMod Error n-" + std::to_string(this->_code) + " : " + FMOD_ErrorString(this->_code) + ".";
        return message.c_str();
    }

    void FMod_Error::check(FMOD_RESULT code, bool throws) {
        if(code != FMOD_OK) {
            if(throws) {
                throw FMod_Error(code);
            }
            else {
                std::cerr << "FMOD Error n-" << code << " : " <<  FMOD_ErrorString(code) << std::endl; 
            }
            
        }
    }
}