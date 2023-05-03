#include <common/numbers.h>

//////////////////// Constructor
Numbers::Numbers(Display64Led* display) {
    m_display = display;
}

//////////////////// Public methods implementation
void Numbers::printNumber(byte number) {
    switch (number) {
    case 0:
        printZero();
        break;
    case 1:
        printOne();
        break;
    case 2:
        printTwo();
        break;
    case 3:
        printThree();
        break;
    default:
        break;
    }
}

//////////////////// Private methods implementation
void Numbers::printZero() {
    for (byte i = 0; i < 8; i++)
        for (byte j = 0; j < 8; j++)
            m_display->setPixel(i, j, (zero[i][j] == 1 ? true : false));
}

void Numbers::printOne() {
    for (byte i = 0; i < 8; i++)
        for (byte j = 0; j < 8; j++)
            m_display->setPixel(i, j, (one[i][j] == 1 ? true : false));
}

void Numbers::printTwo() {
    for (byte i = 0; i < 8; i++)
        for (byte j = 0; j < 8; j++)
            m_display->setPixel(i, j, (two[i][j] == 1 ? true : false));
}

void Numbers::printThree() {
    for (byte i = 0; i < 8; i++)
        for (byte j = 0; j < 8; j++)
            m_display->setPixel(i, j, (three[i][j] == 1 ? true : false));
}
