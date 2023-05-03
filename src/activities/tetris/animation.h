#ifndef TetrisAnimation_h
#define TetrisAnimation_h

#include <platform/display64led.h>
#include <platform/timer.h>

class TetrisAnimation {
    private:
        Display64Led* m_display;
        Timer* m_tmrAnimate;

        byte m_line;
    
    public:
        TetrisAnimation(Display64Led *display);

        void start();
        void refresh();
        bool isRunning();
};

#endif
