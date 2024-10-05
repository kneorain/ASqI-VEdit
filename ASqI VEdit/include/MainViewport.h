#ifndef _MAIN_VIEWPORT_H
#define _MAIN_VIEWPORT_H

#include <Panel.h>

#include "Resizeable.h"

class MainViewport : public Panel, public Resizeable {
public:
    MainViewport(SDL_Renderer* renderer) 
     : Panel(renderer,
         {0, 0, 1150, 700},
         {77, 77, 77, 255}
            )
    { }

    void draw() override;
    void resize() override;

private:
    
};

#endif