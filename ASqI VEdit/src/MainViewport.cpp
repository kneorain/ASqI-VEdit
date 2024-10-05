#include <MainViewport.h>
#include <Defines.h>

void MainViewport::draw() {
    Panel::draw();
}

void MainViewport::resize() {
    this->setSize(
        *m_width - ceil(*m_width / SIDE_PANEL_PERCENT),
        *m_height - ceil(*m_height / BOTTOM_PANEL_PERCENT)
        );
}
