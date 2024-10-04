#ifndef _BOTTOM_PANEL_H
#define _BOTTOM_PANEL_H

#include <Panel.h>

class BottomPanel : public Panel {
public:
    BottomPanel(SDL_Renderer* renderer) 
        : Panel(renderer, {0, 500, 1000, 100}, {0, 0, 255, 255}) {} // Blue color

    void draw() override {
        // Custom drawing code for the bottom panel
        Panel::draw();
    }
};


#endif