#ifndef paint_h
#define paint_h

#include <platform/joystick.h>
#include <platform/timer.h>
#include <common/activity.h>
#include <common/gameScore.h>
#include <activities/paint/level.h>

class Paint : public Activity {
    private:
        Display64Led* m_display;
        Joystick* m_joystick;
        PaintLevel* m_gameLevel;
        GameScore* m_gameScore;
        Timer* m_tmrQuit;

        displayPoint m_previousClickPosition, m_currentClickPosition;
        bool m_end;

        byte m_painting[8][8] = {
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
        };

        void resetPainting();
        void composeGameDisplayImage();

    public:
        Paint(Display64Led* display, Joystick* joystic, PaintLevel* gameLevel, GameScore* gameScore);

        String className();
        void start();
        bool loop();
        void action();
};

#endif
