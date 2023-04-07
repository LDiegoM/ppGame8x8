#ifndef ppGameLevel_h
#define ppGameLevel_h

#include <common/gameLevel.h>
#include <platform/timer.h>

class PPGameLevel : public CommonGameLevel {
    private:
        Timer* m_levelTimers[3] = {
            new Timer(2000),
            new Timer(1250),
            new Timer(800)
        };
        Timer* m_currentLevelTimer;

    public:
        PPGameLevel();

        void reset();
        void incLevel();
        void decLevel();
        void restartLevel();
        bool verifyLevel();
};

#endif
