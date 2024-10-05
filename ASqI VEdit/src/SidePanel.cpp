#include <SidePanel.h>
#include <cmath>

#include "imgui.h"
#include "Defines.h"

void SidePanel::draw() const {
    ImGui::SetNextWindowPos(
            ImVec2(ceil(*m_width / SIDE_PANEL_OFFSET), 0)
            );
    ImGui::SetNextWindowSize(
        ImVec2(ceil(*m_width / SIDE_PANEL_PERCENT), ceil(*m_height - ceil(*m_height / BOTTOM_PANEL_PERCENT)))
        );
        
    ImGui::Begin("Side Panel", nullptr, 
                 ImGuiWindowFlags_NoCollapse | 
                 ImGuiWindowFlags_NoResize | 
                 ImGuiWindowFlags_NoTitleBar);
        
    ImGui::Text("This is the side panel!");

    ImGui::End();
}

void SidePanel::resize() { }