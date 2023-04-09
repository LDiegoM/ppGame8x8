#ifndef joystick_h
#define joystick_h

#include <Arduino.h>
#include <platform/display64led.h>

class Joystick {
    private:
        byte m_pinJoystickX, m_pinJoystickY;

    public:
        Joystick(byte pinJoystickX, byte pinJoystickY);

        displayPoint getPosition();
};

#endif
