#ifndef gameScore_h
#define gameScore_h

#include <Arduino.h>
#include <shiftRegisters.h>
#include <timer.h>

extern const byte STARTING_SCORE;
extern byte currentScore;

class GameScore {
    private:
        // Game Score is composed by a 7 segment display and a green/red led that
        // indicates if hit or miss the random point. Theese components are connected
        // to a 74HC595 ic (shift registed)
        ShiftRegisters* m_shiftRegisters;
        byte m_shiftRegisterNumber;
        byte m_currentScore;
        bool m_pointWon;
        Timer* m_ledTimer;

    public:
        GameScore(ShiftRegisters* shiftRegisters, byte shiftRegisterNumber);

        void showScoreLed(bool pointWon);
        void showNewScore(byte score);
        void refresh();
};

#endif