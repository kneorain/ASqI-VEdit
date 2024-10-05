#ifndef _BOTTOM_PANEL_H
#define _BOTTOM_PANEL_H

#include "DrawableContainer.h"
#include "Resizeable.h"

class BottomPanel : public Resizeable, public DrawableContainer {
public:
    BottomPanel() = default;
    
    void draw() const;
    void resize() override;
};

#endif
