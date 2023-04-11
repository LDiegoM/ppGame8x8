#ifndef ppGame_h
#define ppGame_h

#include <Arduino.h>
#include <platform/display64led.h>
#include <platform/joystick.h>
#include <common/activity.h>
#include <common/gameScore.h>
#include <activities/ppGame/level.h>

class PPGame : public Activity {
    private:
        Display64Led* m_display;
        Joystick* m_joystick;
        PPGameLevel* m_gameLevel;
        GameScore* m_gameScore;

        // Handle no action made by player. If player doesn't press the button for 5 cycles, loses 1 point
        const byte MAX_NO_ACTION_CYCLES = 5;
        byte m_noActionCount;

        bool m_gameRunning;
        displayPoint m_playerPosition, m_randomPosition;

        void startNewGame();
        void endGame();
        displayPoint getRandomPoint();
        bool evaluateHitOrMiss();
        void composeGameDisplayImage();

    public:
        PPGame(Display64Led* display, Joystick* joystic, PPGameLevel* gameLevel, GameScore* gameScore);

        String className();
        void start();
        bool loop();
        void action();
};

#endif
