#ifndef _BOTTOM_PANEL_H
#define _BOTTOM_PANEL_H

#include <SDL_render.h>

#include "DrawableContainer.h"
#include "Resizeable.h"

class BottomPanel : public Resizeable, public DrawableContainer {
public:
    BottomPanel(SDL_Renderer* renderer);
    
    void draw() const;
    void resize() override;

private:
    SDL_Renderer* m_renderer;
};

#endif
