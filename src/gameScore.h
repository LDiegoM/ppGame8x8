#ifndef gameScore_h
#define gameScore_h

#include <Arduino.h>
#include <shiftRegisters.h>
#include <timer.h>

extern const byte STARTING_SCORE;

// Implements 3 game levels
extern Timer* levelTimers[];
extern byte levelCount;
extern Timer* levelTimer;

class GameScore {
    private:
        // Game Score is composed by a 7 segment display and a green/red led that
        // indicates if hit or miss the random point. Theese components are connected
        // to a 74HC595 ic (shift registed)
        ShiftRegisters* m_shiftRegisters;
        byte m_shiftRegisterNumber;

        byte m_currentLevel;
        bool m_levelChanged = false;

        byte m_currentScore;
        bool m_pointWon;

        bool m_gameEnd;

        Timer* m_ledTimer;

        byte currentLevelToShiftValue();

    public:
        GameScore(ShiftRegisters* shiftRegisters, byte shiftRegisterNumber);

        void resetScoreAndLevel();
        void calculateScoreAndLevel(bool pointWon);
        bool gameEnd();
        void showScoreLed(bool pointWon);
        void showCurrentScore();
        void refresh();
};

#endif