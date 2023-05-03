#include <activities/tetris/level.h>

//////////////////// Constructor
TetrisLevel::TetrisLevel() {
    m_levelCount = sizeof(m_levelTimers) / sizeof(Timer*);
    m_currentLevelTimer = m_levelTimers[0];
}

//////////////////// Public methods implementation
void TetrisLevel::reset() {
    m_currentLevel = 1;
    m_currentLevelTimer = m_levelTimers[m_currentLevel - 1];
}

void TetrisLevel::incLevel() {
    m_currentLevel++;
    m_currentLevelTimer = m_levelTimers[m_currentLevel - 1];
}

void TetrisLevel::decLevel() {
    m_currentLevel--;
    m_currentLevelTimer = m_levelTimers[m_currentLevel - 1];
}

void TetrisLevel::restartLevel() {
    m_currentLevelTimer->start();
}

bool TetrisLevel::verifyLevelLimit() {
    return m_currentLevelTimer->isTime();
}

//////////////////// Private methods implementation
