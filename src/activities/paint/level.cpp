#include <activities/paint/level.h>

//////////////////// Constructor
PaintLevel::PaintLevel() {
    m_levelCount = 3;
}

//////////////////// Public methods implementation
void PaintLevel::reset() {
    m_currentLevel = 2;
}

void PaintLevel::incLevel() {
    reset();
}

void PaintLevel::decLevel() {
    reset();
}

void PaintLevel::restartLevel() {}

bool PaintLevel::verifyLevelLimit() {
    return false;
}

//////////////////// Private methods implementation
