#include <Panel.h>
#include "Utils.h"

void Panel::setSize(const int width, const int height) {
    m_rect.w = width;
    m_rect.h = height;
}

inline void Panel::setSize(const IntVec2 size) {
    setSize(size.x, size.y);
}

void Panel::setPosition(const int x, const int y) {
    m_rect.x = x;
    m_rect.y = y;
}

inline void Panel::setPosition(IntVec2 position) {
    setPosition(position.x, position.y);
}

void Panel::draw() {
    SDL_SetRenderDrawColor(m_renderer, m_color.r, m_color.g, m_color.b, m_color.a);
        SDL_RenderFillRect(m_renderer, &m_rect);
}
