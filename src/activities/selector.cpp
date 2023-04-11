#include <activities/selector.h>

//////////////////// Constructor
Selector::Selector(Display64Led* display, Joystick* joystick) {
    m_numbers = new Numbers(display);
    m_display = display;
    m_joystick = joystick;
}

//////////////////// Public methods implementation
String Selector::className() {
    return "Selector";
}

void Selector::start() {
    m_selected = false;
    m_alreadySwitched = false;
    m_currentValue = 1;
    m_display->resetDisplayImage();
    printValue();
}

bool Selector::loop() {
    if (m_selected)
        return false;

    m_joystickPosition = m_joystick->getPosition();

    switch (joystickAction()) {
        case -1:
            if (m_alreadySwitched || m_currentValue <= MIN_VALUE)
                return true;
            m_alreadySwitched = true;
            m_currentValue--;
            printValue();
            break;
        case 0:
            m_alreadySwitched = false;
            break;
        case 1:
            if (m_alreadySwitched || m_currentValue >= MAX_VALUE)
                return true;
            m_alreadySwitched = true;
            m_currentValue++;
            printValue();
            break;
    }

    return true;
}

void Selector::action() {
    m_selected = true;
    m_nextActivityIndex = m_currentValue;
}

//////////////////// Private methods implementation
int8_t Selector::joystickAction() {
    if (m_joystickPosition.x <= 1 || m_joystickPosition.y <= 1)
        return -1;

    if (m_joystickPosition.x >= 6 || m_joystickPosition.y >= 6)
        return 1;

    return 0;
}

void Selector::printValue() {
    m_numbers->printNumber(m_currentValue);
}
