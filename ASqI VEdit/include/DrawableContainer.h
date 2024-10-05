#ifndef _DRAWABLE_CONTAINER_H
#define _DRAWABLE_CONTAINER_H

#include <functional>
#include <string>
#include <unordered_map>

#include "Drawable.h"

class DrawableContainer {
public:
    void add(const std::string& key, Drawable* obj);
    Drawable* get(const std::string& key);

protected:
    std::unordered_map<std::string, Drawable*> m_objects;
};

#endif