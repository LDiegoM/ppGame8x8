#ifndef selector_h
#define selector_h

#include <platform/display64led.h>
#include <platform/joystick.h>
#include <common/activity.h>
#include <common/numbers.h>

class Selector : public Activity {
    private:
        const byte MIN_VALUE = 0, MAX_VALUE = 2;

        Numbers* m_numbers;
        Display64Led* m_display;
        Joystick* m_joystick;

        displayPoint m_joystickPosition;
        bool m_selected, m_alreadySwitched;
        // Starts as default with first activity. Zero will be back to animation
        byte m_currentValue = 1;

        int8_t joystickAction();
        void printValue();

    public:
        Selector(Display64Led* display, Joystick* joystic);

        String className();
        void start();
        bool loop();
        void action();
};

#endif
