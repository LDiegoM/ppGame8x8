#ifndef animation_h
#define animation_h

#include <platform/timer.h>
#include <platform/display64led.h>
#include <common/activity.h>

class Animation : public Activity {
    private:
        struct animationPoint {
            bool value;
            byte x;
            byte y;
        };

        animationPoint animationPoints[24] = {
            {true, 0, 4}, {true, 1, 5}, {true, 1, 6}, {true, 3, 4}, {true, 2, 6}, {true, 3, 7},
            {true, 4, 7}, {true, 5, 6}, {true, 6, 6}, {true, 4, 4}, {true, 6, 5}, {true, 7, 4},
            {true, 7, 3}, {true, 6, 2}, {true, 6, 1}, {true, 4, 3}, {true, 5, 1}, {true, 4, 0},
            {true, 3, 0}, {true, 2, 1}, {true, 1, 1}, {true, 3, 3}, {true, 1, 2}, {true, 0, 3}
        };
        const byte lenAnimationPoints = sizeof(animationPoints) / sizeof(animationPoint);
        
        byte m_currentAnimationPoint;
        Timer* m_animationTimer;
        Display64Led* m_display;

        void animateImage();

    public:
        Animation(Display64Led* display);

        String className();
        void start();
        bool loop();
        void action();
};

#endif
