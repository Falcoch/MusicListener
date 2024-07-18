#include "TimeSlider.hpp"

#include <chrono>
#include <imgui.h>
#include <imgui_internal.h>

#include "../../interfaces/Player.hpp"

#include <iostream>

namespace tock::interface::player {
    TimeSlider::TimeSlider(Player * parent) 
    : Component(parent), _value(0), _modify(false) {}

    void TimeSlider::render(double time) {
        audio::Sound * sound = this->parent()->currentTrack();
        unsigned int soundLenght = sound != nullptr ? sound->lenght() : 0;

        if(!this->_modify && sound != nullptr) {
            this->_value = this->parent()->player().getPosition()/1000;
        }
        ImGui::PushItemWidth(this->parent()->window().width());
        ImGui::SliderInt("##Music Slider", &this->_value, 0, soundLenght/1000, "%0");  
            
        if(ImGui::IsItemActive()) {
            this->_modify = true;
        }         

        if(ImGui::IsItemDeactivated()) {
            this->_modify = false;
            this->parent()->changePosition(this->_value*1000);
        }

        std::chrono::milliseconds milisecondElapsed(this->parent()->player().getPosition());
        std::chrono::milliseconds milisecondMax(soundLenght);

        std::chrono::seconds seconds = std::chrono::duration_cast<std::chrono::seconds>(milisecondElapsed % std::chrono::minutes(1));
        std::chrono::minutes minutes = std::chrono::duration_cast<std::chrono::minutes>(milisecondElapsed);

        std::chrono::seconds seconds_max = std::chrono::duration_cast<std::chrono::seconds>(milisecondMax % std::chrono::minutes(1));
        std::chrono::minutes minutes_max = std::chrono::duration_cast<std::chrono::minutes>(milisecondMax);

        ImGui::Text("  %u:%s%u / %u:%s%u", 
            minutes,
            seconds < std::chrono::seconds(10) ? "0" : "",
            seconds, 
            minutes_max,
            seconds_max < std::chrono::seconds(10) ? "0" : "",
            seconds_max
        );

        int milisecond = (this->_value*1000)-this->parent()->player().getPosition();
        if(this->_modify && milisecond != 0) {
                
            milisecond /= 1000;

            int second = milisecond % 60;
            int minute = milisecond / 60;

            bool positive = milisecond >= 0;
            ImVec4 color = positive ? ImVec4(0.25f, 0.85f, 0.25f, 1.f) : ImVec4(85.f, 0.25f, 0.25f, 1.f);

            std::string str_m = "?";
            str_m.append(std::to_string(abs(minute)));
            str_m.append(":00  ");

            ImGui::SameLine(ImGui::GetWindowWidth() - ImGui::CalcTextSize(str_m.c_str()).x);
            ImGui::TextColored(color ,"%c%d:", (positive ? '+' : '-'),  abs(minute));
            ImGui::SameLine(ImGui::GetWindowWidth() - ImGui::CalcTextSize("00  ").x);
            ImGui::TextColored(color, "%s%d", (abs(second) < 10) ? "0" : "", abs(second));
        }
        else {
            ImGui::SameLine(ImGui::GetWindowWidth() - ImGui::CalcTextSize("~0:00  ").x);
            ImGui::TextColored(ImVec4(0.25f, 0.25f, 1.f, 1.f) ,"~0:00  ");
        }
    }
}