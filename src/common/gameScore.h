#ifndef gameScore_h
#define gameScore_h

#include <platform/shiftRegisters.h>
#include <platform/timer.h>
#include <common/gameLevel.h>

class GameScore {
    private:
        // Game Score is composed by a 7 segment display and a green/red led that
        // indicates if hit or miss the random point. Theese components are connected
        // to a 74HC595 ic (shift registed)
        ShiftRegisters* m_shiftRegisters;
        byte m_shiftRegisterNumber;
        CommonGameLevel *m_gameLevel;

        bool m_levelChanged = false;

        byte m_startingScore;
        byte m_currentScore;
        bool m_pointWon;

        bool m_gameEnd;

        Timer* m_ledTimer;

        byte m_pinBuzzer;
        const unsigned int WON_TONE  = 2093;
        const unsigned int LOSE_TONE = 1047;

        byte currentLevelToShiftValue();
        void showCurrentScore();

    public:
        GameScore(CommonGameLevel *gameLevel, ShiftRegisters* shiftRegisters, byte shiftRegisterNumber, byte pinBuzzer,
                  byte startingScore);

        void reset();
        void calculate(bool pointWon);
        void showScoreLed(bool pointWon);
        bool gameEnd();
        void refresh();
};

#endif