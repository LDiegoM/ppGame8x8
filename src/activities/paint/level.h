#ifndef paintLevel_h
#define paintLevel_h

#include <common/gameLevel.h>

class PaintLevel : public CommonGameLevel {
    private:

    public:
        PaintLevel();

        void reset();
        void incLevel();
        void decLevel();
        void restartLevel();
        bool verifyLevelLimit();
};

#endif
