#include <activities/paint/paint.h>

//////////////////// Constructor
Paint::Paint(Display64Led* display, Joystick* joystic, PaintLevel* gameLevel, GameScore* gameScore) {
    m_display = display;
    m_joystick = joystic;
    m_gameLevel = gameLevel;
    m_gameScore = gameScore;

    m_tmrQuit = new Timer(500);
}

//////////////////// Public methods implementation
String Paint::className() {
    return "Paint";
}

void Paint::start() {
    m_end = false;

    m_gameScore->reset();

    resetPainting();
    m_display->resetDisplayImage();
}

bool Paint::loop() {
    if (m_end)
        return false;

    if (m_tmrQuit->isTime())
        m_tmrQuit->stop();

    composeGameDisplayImage();

    return true;
}

void Paint::action() {
    m_previousClickPosition = m_currentClickPosition;
    m_currentClickPosition = m_joystick->getPosition();

    if (m_previousClickPosition.x == m_currentClickPosition.x &&
        m_previousClickPosition.y == m_currentClickPosition.y) {

        if (m_tmrQuit->isRunning())
            m_end = true;
        else
            m_tmrQuit->start();
        
        return;
    }

    m_painting[m_currentClickPosition.x][m_currentClickPosition.y] = 1;
}

//////////////////// Private methods implementation
void Paint::resetPainting() {
    for (byte x = 0; x < 8; x++)
        for (byte y = 0; y < 8; y++)
            m_painting[x][y] = 0;
}

void Paint::composeGameDisplayImage() {
    displayPoint position = m_joystick->getPosition();

    for (byte x = 0; x < 8; x++) {
        for (byte y = 0; y < 8; y++) {
            if ((position.x == x && position.y == y) || (m_painting[x][y] == 1))
                m_display->setPixel(x, y, true);
            else
                m_display->setPixel(x, y, false);
        }
    }
}
