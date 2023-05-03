#include <activities/tetris/animation.h>

//////////////////// Constructor
TetrisAnimation::TetrisAnimation(Display64Led *display) {
    m_display = display;
    m_tmrAnimate = new Timer(40);
}

//////////////////// Public methods implementation
void TetrisAnimation::start() {
    m_line = 0;

    for (byte y = 0; y < 8; y++)
        m_display->setPixel(m_line, y, true);

    m_tmrAnimate->start();
}

void TetrisAnimation::refresh() {
    if (!m_tmrAnimate->isTime())
        return;
    
    for (byte y = 0; y < 8; y++)
        m_display->setPixel(m_line, y, false);

    if (m_line >= 8) {
        m_tmrAnimate->stop();
        return;
    }

    m_line++;

    for (byte y = 0; y < 8; y++)
        m_display->setPixel(m_line, y, true);
}

bool TetrisAnimation::isRunning() {
    return m_tmrAnimate->isRunning();
}

//////////////////// Private methods implementation
