#include <common/gameLevel.h>

//////////////////// Public methods implementation
byte CommonGameLevel::levelCount() {
    return m_levelCount;
}

byte CommonGameLevel::currentLevel() {
    return m_currentLevel;
}

bool CommonGameLevel::isAtFirstLevel() {
    return m_currentLevel <= 1;
}

bool CommonGameLevel::isAtLastLevel() {
    return m_currentLevel >= m_levelCount;
}
