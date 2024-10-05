#include <SidePanel.h>
#include <cmath>

#include "imgui.h"
#include "Defines.h"
#include "imgui_internal.h"
#include "Utils.h"

#define NODE_SIZE 72

SidePanel::SidePanel(SDL_Renderer* renderer) : m_renderer(renderer) {
    m_tooltipFont = loadFont(12.0, REGULAR);
}

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

    const ImVec2 availableSpace = ImGui::GetContentRegionAvail();
    const float spacing = ImGui::GetStyle().ItemSpacing.x;
    int count = 0;
    const ImVec2 framePadding = ImGui::GetStyle().FramePadding;
    const int effectiveButtonSize = NODE_SIZE - (framePadding.x * 2);  // Adjust for frame padding
    const int columns = std::max(1, (int)((availableSpace.x + spacing) / (NODE_SIZE + spacing)));
    
    for (const std::string& name : m_nodes) {
        ImGui::PushID(name.c_str());
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.f, 0.f, 0.f, 0.f));
        
        
        if (count % columns == 0) {
            const float totalRowWidth = (columns * NODE_SIZE) + ((columns - 1) * spacing);
            const float offsetX = (availableSpace.x - totalRowWidth) * 0.5f + spacing;
            ImGui::SetCursorPosX(offsetX);
        }

        std::string filename = "assets/nodes/" + name + ".png";
        std::replace(filename.begin(), filename.end(), ' ', '_');
        
        SDL_Texture* btnImg = loadTextureFromFile(m_renderer, filename.c_str());
        if (ImGui::ImageButton(name.c_str(), btnImg, ImVec2(effectiveButtonSize, effectiveButtonSize))) { }

        if (ImGui::BeginDragDropSource()) {
            *m_dragTarget = name;
            ImGui::SetDragDropPayload("DRAG_DROP_ITEM", nullptr, 0);
            ImGui::Text("%s", name.c_str()); // Optional: Display the item being dragged
            ImGui::EndDragDropSource(); // End the drag-and-drop source
        }

        if (ImGui::IsItemHovered()) {
            ImGui::PushFont(m_tooltipFont);
            ImGui::BeginTooltip();
            ImGui::Text(name.c_str());
            ImGui::EndTooltip();
            ImGui::PopFont();
        }
        
        ImGui::PopStyleColor();
        ImGui::PopID();
        count++;
        
        if (count % columns != 0) {
            ImGui::SameLine();
        } else {
            ImGui::Spacing();
        }
    }

    
    ImGui::End();
}

void SidePanel::resize() { }

void SidePanel::setDragTarget(std::string* dragTarget) {
    m_dragTarget = dragTarget;
}
