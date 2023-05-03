#ifndef TetrisGame_h
#define TetrisGame_h

#include <platform/display64led.h>
#include <platform/joystick.h>
#include <common/activity.h>
#include <common/gameScore.h>
#include <activities/tetris/level.h>
#include <activities/tetris/animation.h>

#include <activities/tetris/blockT.h>

class Tetris : public Activity {
    private:
        Display64Led* m_display;
        Joystick* m_joystick;
        TetrisLevel* m_gameLevel;
        GameScore* m_gameScore;

        TetrisAnimation* m_animation;
        bool m_gameRunning;
        displayPoint m_joystickPosition;

        void composeGameDisplayImage();

    public:
        Tetris(Display64Led* display, Joystick* joystic, TetrisLevel* gameLevel, GameScore* gameScore);

        String className();
        void start();
        bool loop();
        void action();

};

#endif
