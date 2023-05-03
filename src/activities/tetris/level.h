#ifndef TetrisLevel_h
#define TetrisLevel_h

#include <platform/timer.h>
#include <common/gameLevel.h>

class TetrisLevel : public CommonGameLevel {
    private:
        Timer* m_levelTimers[3] = {
            new Timer(2000),
            new Timer(1250),
            new Timer(800)
        };
        Timer* m_currentLevelTimer;

    public:
        TetrisLevel();

        void reset();
        void incLevel();
        void decLevel();
        void restartLevel();
        bool verifyLevelLimit();
};

#endif
