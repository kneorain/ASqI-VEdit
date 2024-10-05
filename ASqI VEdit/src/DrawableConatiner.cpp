#include <DrawableContainer.h>

void DrawableContainer::add(const std::string& key, Drawable* obj) {
    m_objects[key] = obj;
}

Drawable* DrawableContainer::get(const std::string& key) {
    try {
        return m_objects[key];
    } catch (const std::exception& e) {
        (void)fprintf(stderr, "Invalid element key '%s'!", e.what());
        return nullptr;
    }
}
