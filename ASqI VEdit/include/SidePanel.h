#ifndef _SIDE_PANEL_H
#define _SIDE_PANEL_H

#include <string>
#include <unordered_map>

#include "Drawable.h"
#include "DrawableContainer.h"
#include "Resizeable.h"

class SidePanel : public Resizeable, public DrawableContainer {
public:
    SidePanel() = default;
    
    void draw() const;
    void resize() override;

private:
    std::unordered_map<std::string, Drawable> m_objects;
};

#endif
