#ifndef gameScore_h
#define gameScore_h

#include <platform/shiftRegisters.h>
#include <platform/timer.h>

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

        byte m_pinBuzzer;
        const unsigned int WON_TONE  = 2093;
        const unsigned int LOSE_TONE = 1047;

        byte currentLevelToShiftValue();
        void showScoreLed(bool pointWon);
        void showCurrentScore();

    public:
        GameScore(ShiftRegisters* shiftRegisters, byte shiftRegisterNumber, byte pinBuzzer);

        void resetScoreAndLevel();
        void calculateScoreAndLevel(bool pointWon);
        bool gameEnd();
        void refresh();
};

#endif