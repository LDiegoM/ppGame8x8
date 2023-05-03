#include <activities/tetris/block.h>

//////////////////// Constructor
Block::Block(displayPoint location) {
    m_currentLocation = location;
    m_previousLocation = NULL;
    m_currentPosition = blockPosition(random(4));
    m_previousPosition = NULL;
}

//////////////////// Public methods implementation
blockPosition Block::currentPosition(){ 
    return m_currentPosition;
}

byte pointQty() {
    return 4;
}

//////////////////// Private methods implementation
