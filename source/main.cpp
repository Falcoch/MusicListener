#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "../include/fmod/fmod_studio.h"
#include "../include/fmod/fmod_studio.hpp"
#include "../include/fmod/fmod.h"
#include "../include/fmod/fmod_errors.h"

#include "audio/Player.hpp"
#include "audio/MetaData.hpp"
#include "utils/Window.hpp"

#include "interface/Renderer.hpp"
#include "interface/interfaces/Player.hpp"

#define WINDOW_WIDTH 360
#define WINDOW_HEIGHT 520

int main(int argc, const char * argv[]) {
    try { 
        tock::utils::Window window("Audio Player", WINDOW_WIDTH, WINDOW_HEIGHT);
        window.open();

        tock::audio::Player player;
        tock::interface::Renderer renderer(window);
        tock::interface::Player interface(renderer, player);

        renderer.push(interface);

        double time = 0.0;

        std::cout << "Render Loop Begin" << std::endl;
        
        do {
            time = tock::utils::Window::CurrentTime();
            window.pollEvents();
            
            renderer.show(time);
            renderer.update(time);

            window.swapBuffers();

        } while(window.isOpen());

        std::cout << "Render Loop End" << std::endl;
    }
    catch(std::exception & error) {
        std::cerr << error.what() << std::endl;
    }
    
    return EXIT_SUCCESS;
}