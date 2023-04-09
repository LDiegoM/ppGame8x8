#include <platform/joystick.h>

//////////////////// Constructor
Joystick::Joystick(byte pinJoystickX, byte pinJoystickY) {
    m_pinJoystickX = pinJoystickX;
    m_pinJoystickY = pinJoystickY;
}

//////////////////// Public methods implementation
displayPoint Joystick::getPosition() {
    displayPoint point;
    point.x = map(analogRead(m_pinJoystickX), 0, 1024, 0, 8);
    point.y = map(analogRead(m_pinJoystickY), 0, 1024, 0, 8);
    return point;
}

//////////////////// Private methods implementation
