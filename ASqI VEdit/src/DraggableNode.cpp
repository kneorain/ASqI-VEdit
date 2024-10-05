#include <DraggableNode.h>

DraggableNode::DraggableNode(SDL_Surface* nodeImage, IntVec2 size) : m_image(nodeImage) {
    if (nodeImage->w != size.x || nodeImage->h != size.y) {
        
    }
}

void DraggableNode::draw() {
    
}
