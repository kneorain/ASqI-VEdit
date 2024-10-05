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
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;

    int m_windWidth = 1500;
    int m_windHeight = 900;
    
    ImGuiIO* m_io;
    ImGuiContext* m_context;

    MainViewport* m_mainViewport;
    SidePanel* m_sidePanel;
    BottomPanel* m_bottomPanel;

    bool init();
    void kill() const;

    void initViewportUI();
    void initSidePanelUI();
    void initBottomPanelUI();
};

#endif