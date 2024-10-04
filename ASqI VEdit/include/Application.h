#ifndef _APPLICATION_H
#define _APPLICATION_H

#include <SDL.h>

#include "imgui.h"
#include "BottomPanel.h"
#include "MainViewport.h"
#include "SidePanel.h"

class Application {
public:
    Application();

    void run();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    
    ImGuiIO* io;
    ImGuiContext* context;

    MainViewport* mainViewport;
    SidePanel* sidePanel;
    BottomPanel* bottomPanel;

    bool init();
    void kill();
};

#endif