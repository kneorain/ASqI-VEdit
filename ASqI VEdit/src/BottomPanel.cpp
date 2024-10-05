#include <BottomPanel.h>
#include <cmath>

#include "imgui.h"
#include "Defines.h"

void BottomPanel::draw() const {
    ImGui::SetNextWindowPos(ImVec2(0, *m_height - ceil(*m_height / BOTTOM_PANEL_PERCENT)));
    ImGui::SetNextWindowSize(ImVec2(*m_width, ceil(*m_height / BOTTOM_PANEL_PERCENT)));

    ImGui::Begin("Bottom Panel", nullptr, 
                 ImGuiWindowFlags_NoCollapse | 
                 ImGuiWindowFlags_NoResize | 
                 ImGuiWindowFlags_NoTitleBar);

    // Draw child objects
    for (const std::pair<std::string, Drawable*> obj : m_objects) {
        obj.second->draw();
    }
        
    ImGui::End();
}

void BottomPanel::resize() { }