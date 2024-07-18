#pragma once

#include <iostream>


#ifdef _WIN32
    #include <windows.h>
    #include <shobjidl.h>
    #define GLFW_EXPOSE_NATIVE_WIN32
#endif


#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include "Window.hpp"

namespace tock::os {
    void setWindowProgressBar(Window & window, unsigned long completed, unsigned long total) {
        if(!window.address().has_value()) {
            return;
        }

        /*
        #ifdef _WIN32
            HWND windowHandle = glfwGetWin32Window(window.address().value());
            ITaskbarList3 * taskBar;
            HRESULT result = CoCreateInstance(CLSID_TaskbarList, NULL, CLSCTX_ALL, IID_PPV_ARGS(&taskBar));

            if(SUCCEEDED(result)) {
                taskBar->HrInit();
                taskBar->SetProgressValue(windowHandle, completed, total);
                taskBar->Release();
            }
        #endif
        */
    }

    enum BarStatue {
        NORMAL, 
        ERRORS,
        NO_PROGRESS,
        PAUSED,
        INDETERMINED
    };

    void setWindowStatueBar(Window & window, BarStatue status) {
        if(!window.address().has_value()) {
            return;

            /*
            #ifdef _WIN32
                HWND windowHandle = glfwGetWin32Window(window.address().value());
                ITaskbarList3 * taskBar;
                HRESULT result = CoCreateInstance(CLSID_TaskbarList, NULL, CLSCTX_ALL, IID_PPV_ARGS(&taskBar));

                TBPFLAG status = TBPF_NORMAL;

                switch (status) {
                    case BarStatue::ERRORS:
                        status = TBPF_ERROR;
                        break;

                    case BarStatue::NO_PROGRESS:
                        status = TBPF_NOPROGRESS;
                        break;

                    case BarStatue::PAUSED:
                        status = TBPF_PAUSED;
                        break;

                    case BarStatue::INDETERMINED:
                        status = TBPF_INDETERMINATE;
                        break;
                
                    default:
                        status = TBPF_NORMAL;
                        break;
                }


                if(SUCCEEDED(result)) {
                    taskBar->HrInit();
                    taskBar->SetProgressState(windowHandle, status);
                    taskBar->Release();
                }
            #endif
            */
        }
    }
}