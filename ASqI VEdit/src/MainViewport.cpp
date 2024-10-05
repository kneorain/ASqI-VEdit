#include <MainViewport.h>
#include <Defines.h>

#include "imgui.h"

void MainViewport::draw() {
    Panel::draw();

    // Transparent overlay for interactivity
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(
        *m_width - ceil(*m_width / SIDE_PANEL_PERCENT),
        *m_height - ceil(*m_height / BOTTOM_PANEL_PERCENT))
    );
    ImGui::SetNextWindowBgAlpha(0.0f);
    ImGui::Begin(
        "Transparent Overlay", nullptr,
        ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse
        );

    // ᓚᘏᗢ
    ImGui::InvisibleButton("DropTarget", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y));

    if (ImGui::BeginDragDropTarget()) {
        const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DRAG_DROP_ITEM");

        if (payload) {
            // Add new instance of DraggableNode() to m_objects
            printf("%s\n", m_dragTarget->c_str());
            *m_dragTarget = "";
        }
        
        ImGui::EndDragDropTarget();
    }

    ImGui::End();
}

void MainViewport::resize() {
    this->setSize(
        *m_width - ceil(*m_width / SIDE_PANEL_PERCENT),
        *m_height - ceil(*m_height / BOTTOM_PANEL_PERCENT)
        );
}

void MainViewport::setDragTarget(std::string* dragTarget) {
    m_dragTarget = dragTarget;
}
