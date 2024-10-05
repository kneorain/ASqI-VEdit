#ifndef _PANEL_H
#define _PANEL_H

#include <SDL.h>
#include "Utils.h"

class Panel {
public:
    Panel(SDL_Renderer* renderer, const SDL_Rect rect, const SDL_Color color)
        : m_renderer(renderer), m_rect(rect), m_color(color) { }

    void setSize(int width, int height);
    inline void setSize(IntVec2 size);
    void setPosition(int x, int y);
    inline void setPosition(IntVec2 position);

    virtual void draw();

protected:
    SDL_Renderer* m_renderer;
    SDL_Rect m_rect;
    SDL_Color m_color;
};

#endif