/*
    ppGame8x8 score and level handling.

    This class is a handler to send the current score to a 7 segment display, the pointWon condition
    and the current level indicator.
    The display and the leds are connected to an IC 74HC595 shift register to handle the 4 bits for the
    IC CD4511B, and 1 additional bit to control the IC memory and turn on the leds.
    The 3 leds that inicates he current level are connected to the other 3 pins of the IC.

    Diego M. Lopez - 2021 (ldiegom@gmail.com)
*/

#include <limits.h>
#include <gameScore.h>

const byte STARTING_SCORE = 3;
Timer* levelTimers[] = {
    new Timer(2000, ULONG_MAX, millis),
    new Timer(1250, ULONG_MAX, millis),
    new Timer(800, ULONG_MAX, millis)
};
byte levelCount = sizeof(levelTimers) / sizeof(Timer*);
Timer* levelTimer = levelTimers[0];

//////////////////// Constructor
GameScore::GameScore(ShiftRegisters* shiftRegisters, byte shiftRegisterNumber) {
    m_shiftRegisters = shiftRegisters;
    m_shiftRegisterNumber = shiftRegisterNumber;

    m_currentLevel = 0;
    m_currentScore = 0;
    showCurrentScore();

    m_ledTimer = new Timer(500, ULONG_MAX, millis);
}

//////////////////// Public methods implementation
void GameScore::resetScoreAndLevel() {
    m_gameEnd = false;

    // Choose the easiest game level
    m_currentLevel = 1;
    levelTimer = levelTimers[m_currentLevel - 1];
    m_levelChanged = false;

    // Game starts with score = 3
    m_currentScore = STARTING_SCORE;
    showCurrentScore();
}

void GameScore::calculateScoreAndLevel(bool pointWon) {
    if (pointWon)
        m_currentScore++;
    else
        m_currentScore--;

    if (m_currentScore == 0) {
        m_currentLevel--;
        m_levelChanged = true;
    } else if (m_currentScore > 9) {
        m_currentLevel++;
        m_levelChanged = true;
    } else {
        m_levelChanged = false;
    }

    if (m_levelChanged) {
        levelTimer->stop();
        m_currentScore = STARTING_SCORE;

        if (m_currentLevel <= 0) {
            m_currentScore = 0;
            m_gameEnd = true;
        } else if (m_currentLevel > levelCount) {
            m_currentScore = levelCount;
            m_gameEnd = true;
        }

        if (m_currentLevel >= 1 && m_currentLevel <= levelCount) {
            levelTimer = levelTimers[m_currentLevel - 1];
            levelTimer->start();
        }
    }
    showCurrentScore();
    showScoreLed(pointWon);
}

bool GameScore::gameEnd() {
    return m_gameEnd;
}

void GameScore::refresh() {
    // Send by default the leds turned off and no new value to 7 segment display.
    if (!m_ledTimer->isRunning())
        m_shiftRegisters->setShiftValue(m_shiftRegisterNumber, currentLevelToShiftValue() + 16 + 3);
    else {
        m_shiftRegisters->setShiftValue(m_shiftRegisterNumber, currentLevelToShiftValue() + 16 + (m_pointWon ? 2 : 1));
        if (m_ledTimer->isTime()) {
            m_ledTimer->stop();
        }
    }
}

//////////////////// Private methods implementation
byte GameScore::currentLevelToShiftValue() {
    switch (m_currentLevel) {
        case 0:
            return 224; // 128 + 64 + 32 - All leds off
        case 1:
            return 192; // 128 + 64 - bit 6 off
        case 2:
            return 160; // 128 + 32 - bit 7 off
        case 3:
            return 96; // 64 + 32 - bit 8 off
        case 4: // This value has when game was won
            return 0; // All leds on
    }
    
    return 224; // 128 + 64 + 32 - All leds off
}

void GameScore::showScoreLed(bool pointWon) {
    m_pointWon = pointWon;
    m_ledTimer->start();
}

void GameScore::showCurrentScore() {
    m_shiftRegisters->setShiftValue(m_shiftRegisterNumber, currentLevelToShiftValue() + m_currentScore);
    m_shiftRegisters->sendValues();
}
