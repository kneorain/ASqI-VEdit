#ifndef _SIDE_PANEL_H
#define _SIDE_PANEL_H

#include <string>
#include <unordered_map>
#include <imgui.h>
#include <SDL_render.h>

#include "Drawable.h"
#include "DrawableContainer.h"
#include "Resizeable.h"

class SidePanel : public Resizeable, public DrawableContainer {
public:
    SidePanel(SDL_Renderer* renderer);
    
    void draw() const;
    void resize() override;

    void setDragTarget(std::string* dragTarget);

private:
    SDL_Renderer* m_renderer;
    ImFont* m_tooltipFont;
    std::string* m_dragTarget;
    
    std::unordered_map<std::string, Drawable> m_objects;
    std::string m_nodes[7] = {
        "Step Node", "Note", "Edge Group",
        "Action Node", "External Node", "Dead Node",
        "Snek"
    };
};

#endif
