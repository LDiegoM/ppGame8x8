#ifndef commonGameLevel_h
#define commonGameLevel_h

#include <Arduino.h>

class CommonGameLevel {
    protected:
        byte m_levelCount;
        byte m_currentLevel = 0;

    public:
        byte levelCount();
        byte currentLevel();
        bool isAtFirstLevel();
        bool isAtLastLevel();

        virtual void reset() = 0;
        virtual void incLevel() = 0;
        virtual void decLevel() = 0;
        virtual void restartLevel() = 0;
        virtual bool verifyLevelLimit() = 0;
};

#endif
