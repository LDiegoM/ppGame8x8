#ifndef numbers_h
#define numbers_h

#include <Arduino.h>
#include <platform/display64led.h>

class Numbers {
    private:
        byte zero[8][8] = {
            {0, 1, 1, 1, 1, 1, 1, 0},
            {1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 0, 0, 1, 1, 1},
            {1, 1, 1, 0, 0, 1, 1, 1},
            {1, 1, 1, 0, 0, 1, 1, 1},
            {1, 1, 1, 0, 0, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1},
            {0, 1, 1, 1, 1, 1, 1, 0},
        };

        byte one[8][8] = {
            {0, 0, 0, 1, 1, 1, 0, 0},
            {0, 0, 1, 1, 1, 1, 0, 0},
            {0, 1, 1, 1, 1, 1, 0, 0},
            {0, 0, 0, 1, 1, 1, 0, 0},
            {0, 0, 0, 1, 1, 1, 0, 0},
            {0, 0, 0, 1, 1, 1, 0, 0},
            {0, 0, 0, 1, 1, 1, 0, 0},
            {0, 0, 0, 1, 1, 1, 0, 0},
        };

        byte two[8][8] = {
            {0, 1, 1, 1, 1, 1, 1, 0},
            {1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 0, 0, 1, 1, 1},
            {0, 0, 0, 0, 1, 1, 1, 0},
            {0, 0, 1, 1, 1, 0, 0, 0},
            {1, 1, 1, 0, 0, 0, 0, 0},
            {1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1},
        };

        Display64Led* m_display;

        void printZero();
        void printOne();
        void printTwo();

    public:
        Numbers(Display64Led* display);

        void printNumber(byte number);

};

#endif
