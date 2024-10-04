#ifndef _APPLICATION_H
#define _APPLICATION_H

#include <SDL.h>

#include "BottomPanel.h"
#include "MainViewport.h"
#include "SidePanel.h"

class Application {
public:
    Application() { init(); }

    void run();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    MainViewport* mainViewport;
    SidePanel* sidePanel;
    BottomPanel* bottomPanel;

    bool init();
    bool loop();
    void kill();
};

#endif