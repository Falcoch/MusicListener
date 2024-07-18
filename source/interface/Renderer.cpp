#include "Renderer.hpp"

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

#include <stdexcept>

#include <iostream>

namespace tock::interface {
    Renderer::Renderer(utils::Window & window) 
    : Interface(this), _window(window) {
        std::cerr << "Construct Renderer Interface" << std::endl;
        if(!window.address().has_value()) {
            throw  std::runtime_error("Failled to construt Renderer interface with an invalid Renderer"); 
        }

        if(ImGui::GetCurrentContext() == nullptr) {
            ImGui::CreateContext();
            ImGui_ImplOpenGL3_Init();
            ImGui_ImplGlfw_InitForOpenGL(window.address().value(), true);
        }

        ImGui::StyleColorsDark();

        auto & io = ImGui::GetIO();

        io.IniFilename = nullptr;
        io.LogFilename = nullptr;
    }

    Renderer::~Renderer() {
        std::cerr << "Destroy Renderer Interface" << std::endl;
    }

    void Renderer::fall(Interface<Renderer> & interface) {
        Interface<Renderer> * last = nullptr;
        while(this->_children.size() > 1 || last != &interface) {
            last = &this->_children.top().get();
            this->_children.pop();
        }
    }

    void Renderer::subscribe(Interface<Renderer> & interface) {
        this->_subscriber.push_back(interface);
    }

    void Renderer::unsubscribe(Interface<Renderer> & interface) {
        auto it = this->_subscriber.begin();
        for(; it != this->_subscriber.end(); it++) {
            if(&(it->get()) == &interface) {
                break;
            }
        }
        
        if(it != this->_subscriber.end()) {
            this->_subscriber.erase(it);
        }
    }

    void Renderer::show(double time) {
        glClear(GL_COLOR_BUFFER_BIT);
        if(this->_window.isOpen()) {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            ImGui::SetNextWindowPos(ImVec2(0, 0));
            ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);

            if(!this->_children.empty()) {
                this->_children.top().get().render(time);
            }   
            else {
                this->render(time);
            }

            ImGui::PopStyleVar(1);

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }
    }

    void Renderer::render(double) {
        if(ImGui::Begin("Empty Renderer", NULL, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize)) {
            ImGuiStyle& style = ImGui::GetStyle();
            if(ImGui::Button("Close", ImVec2(this->_window.width(), 32.f))){
                this->_window.close();
            }

            const char * label = "This Renderer interface doesn't have any children !";

            float size = ImGui::CalcTextSize(label).x + style.FramePadding.x * 2.0f;
            float offset = (ImGui::GetContentRegionAvail().x - size) * 0.5f;
                    
            if (offset > 0.0f) {
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + offset);
            }

            ImGui::TextColored(ImVec4(1.f, 0.85f, 0.f, 1.f), label);
        }
        ImGui::End();
    }

    void Renderer::update(double time) {
        for(auto & sub : this->_subscriber) {
            sub.get().update(time);
        }
    }
}