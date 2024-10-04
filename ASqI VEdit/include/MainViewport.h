#ifndef _MAIN_VIEWPORT_H
#define _MAIN_VIEWPORT_H

#include <Panel.h>

class MainViewport : public Panel {
public:
    MainViewport(SDL_Renderer* renderer) 
        : Panel(renderer, {0, 0, 800, 500}, {255, 0, 0, 255}) { }

    void draw() override {
        Panel::draw();
    }
};

#endif