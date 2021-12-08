/*
    ppGame8x8 score handling.

    This class is a handler to send the current score to a 7 segment display and the pointWon condition.
    The display and the leds are connected to an IC 74HC595 shift register to handle the 4 bits for the
    IC CD4511B, and 1 additional bit to control the IC memory and turn on the leds.

    Diego M. Lopez - 2021 (ldiegom@gmail.com)
*/

#include <limits.h>
#include <gameScore.h>

const byte STARTING_SCORE = 3;
byte currentScore = 0;

GameScore::GameScore(ShiftRegisters* shiftRegisters, byte shiftRegisterNumber) {
    m_shiftRegisters = shiftRegisters;
    m_shiftRegisterNumber = shiftRegisterNumber;

    m_ledTimer = new Timer(500, ULONG_MAX, millis);
}

void GameScore::showScoreLed(bool pointWon) {
    m_pointWon = pointWon;
    m_ledTimer->start();
}

void GameScore::showNewScore(byte score) {
    m_shiftRegisters->setShiftValue(m_shiftRegisterNumber, score);
    m_shiftRegisters->sendValues();
}

void GameScore::refresh() {
    // Send by default the leds turned off and no new value to 7 segment display.
    if (!m_ledTimer->isRunning())
        m_shiftRegisters->setShiftValue(m_shiftRegisterNumber, 16 + 3);
    else {
        m_shiftRegisters->setShiftValue(m_shiftRegisterNumber, 16 + (m_pointWon ? 2 : 1));
        if (m_ledTimer->isTime()) {
            m_ledTimer->stop();
        }
    }
}
