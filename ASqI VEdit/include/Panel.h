#ifndef _PANEL_H
#define _PANEL_H

#include <SDL.h>

class Panel {
protected:
    SDL_Renderer* renderer;
    SDL_Rect rect;
    SDL_Color color;

public:
    Panel(SDL_Renderer* renderer, SDL_Rect rect, SDL_Color color)
        : renderer(renderer), rect(rect), color(color) {}

    virtual void draw() {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(renderer, &rect);
    }
};

#endif