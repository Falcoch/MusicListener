#include "OpenButton.hpp"

#include <tinyfiledialogs/tinyfiledialogs.h>
#include "../../interfaces/List.hpp"

#include <iostream>

namespace tock::interface::list {
    OpenButton::OpenButton(List * parent, float size) 
    : Button(parent, "##OpenButton", size, "assets/texture/button/plus.png") {}

    void OpenButton::onPressed(double) {
        const char * filePattern[4] = {"*.mp3", "*.ogg", "*.wav", "*.flac"};
        const char * path = tinyfd_openFileDialog("Music Player", "./", 4, filePattern, "Audio Files", false);

        if(path != NULL) {
            std::cout << "Add : " << std::filesystem::path(path) << std::endl;
        }
    }
}