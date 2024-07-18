#pragma once

#include <filesystem>

#include "../include/fmod/fmod_studio.h"
#include "../include/fmod/fmod_studio.hpp"
#include "../include/fmod/fmod.h"


namespace tock::audio {
    using System    = FMOD::System;
    using Track     = FMOD::Sound;
    using Channel   = FMOD::Channel;
    using Path      = std::filesystem::path;
}
