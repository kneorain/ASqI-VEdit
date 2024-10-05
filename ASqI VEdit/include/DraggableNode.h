#ifndef _DRAGGABLE_H
#define _DRAGGABLE_H

#include <SDL_surface.h>

#include "Drawable.h"
#include "imgui.h"
#include "Utils.h"

enum DraggableState {
    IDLE,
    PREP,
    DRAG,
    DROP
};

class DraggableNode : public Drawable {
public:
    DraggableNode(SDL_Surface* nodeImage, IntVec2 size);
    
    void draw() override;
    
private:
    DraggableState m_state = IDLE;

    ImVec2 m_size;
    ImVec2 m_position;

    SDL_Surface* m_image;
};

#endif