#ifndef _SIDE_PANEL_H
#define _SIDE_PANEL_H

#include <Panel.h>

class SidePanel : public Panel {
public:
    SidePanel(SDL_Renderer* renderer) 
        : Panel(renderer, {800, 0, 200, 500}, {0, 255, 0, 255}) {}

    void draw() override {
        Panel::draw();
    }
};

#endif