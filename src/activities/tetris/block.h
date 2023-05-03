#ifndef TetrisBlock_h
#define TetrisBlock_h

#include <Arduino.h>

#include <platform/display64led.h>

enum blockPosition {up = 0, right = 1, down = 2, left = 3};

class Block {
    protected:
        byte m_bitmap[3][3] = {
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0}
        };

        displayPoint* m_previousLocation;
        displayPoint m_currentLocation;
        blockPosition* m_previousPosition;
        blockPosition m_currentPosition;

    public:
        Block(displayPoint location);

        blockPosition currentPosition();
        displayPoint *currentPoints();
        displayPoint *previousPoints();
        byte pointQty();
        void moveLeft();
        void moveRight();
        void turn();
};

#endif
