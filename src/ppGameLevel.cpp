#include <ppGameLevel.h>

//////////////////// Constructor
PPGameLevel::PPGameLevel() {
    m_levelCount = sizeof(m_levelTimers) / sizeof(Timer*);
    m_currentLevelTimer = m_levelTimers[0];
}

//////////////////// Public methods implementation
void PPGameLevel::reset() {
    m_currentLevel = 1;
    m_currentLevelTimer = m_levelTimers[m_currentLevel - 1];
}

void PPGameLevel::incLevel() {
    m_currentLevel++;
    m_currentLevelTimer = m_levelTimers[m_currentLevel - 1];
}

void PPGameLevel::decLevel() {
    m_currentLevel--;
    m_currentLevelTimer = m_levelTimers[m_currentLevel - 1];
}

void PPGameLevel::restartLevel() {
    m_currentLevelTimer->start();
}

bool PPGameLevel::verifyLevel() {
    return m_currentLevelTimer->isTime();
}

//////////////////// Private methods implementation
