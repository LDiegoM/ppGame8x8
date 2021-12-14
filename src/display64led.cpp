/*
    ppGame8x8 display 8 by 8 handling.

    This class implements a handler that draws the picture led pattern on the display.
    This display is connected to 2 IC 74HC595 shift registers to get the 16 pins logic of the display.
    The most significant ic is connected to the 8 cathodes, so the pins will be in a LOW value to turn on the line.
    The less significant ic is connected to the 8 anodes, so the pins will be in a HIGH value to turn on the line.

    Diego M. Lopez - 2021 (ldiegom@gmail.com)
*/

#include <display64led.h>
#include <shiftRegisters.h>

byte displayImage[8][8] = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
};

void resetDisplayImage() {
    for (byte i = 0; i < 8; i++)
        for (byte j = 0; j < 8; j++)
            displayImage[i][j] = 0;
}

void composeGameDisplayImage(displayPoint playerPosition, displayPoint randomPosition) {
    for (byte x = 0; x < 8; x++) {
        for (byte y = 0; y < 8; y++) {
            if ((playerPosition.x == x && playerPosition.y == y) || 
                (randomPosition.x == x && randomPosition.y == y))
                displayImage[x][y] = 1;
            else
                displayImage[x][y] = 0;
        }
    }
}

//////////////////// Constructor
Display64Led::Display64Led(ShiftRegisters* shiftRegisters, byte shiftRegisterHigh, byte shiftRegisterLow) {
    m_shiftRegisters = shiftRegisters;
    m_shiftRegisterHigh = shiftRegisterHigh;
    m_shiftRegisterLow = shiftRegisterLow;
    resetPoints();
}

//////////////////// Public methods implementation
void Display64Led::refresh() {
    resetPoints();
    for (byte x = 0; x < 8; x++) {
        m_pointX[x] = 0;
        if (x > 0) {
            m_pointX[x - 1] = 0;
        }
        for (byte y = 0; y < 8; y++) {
            if (m_pointX[x] == 0) {
                m_pointX[x] = displayImage[x][y];
            }
            m_pointY[y] = displayImage[x][y];
        }

        m_shiftRegisters->setShiftValue(m_shiftRegisterHigh, 255 - decFromBin(m_pointY));
        m_shiftRegisters->setShiftValue(m_shiftRegisterLow, decFromBin(m_pointX));
        m_shiftRegisters->sendValues();
    }
}

//////////////////// Private methods implementation
byte Display64Led::decFromBin(byte bits[8]) {
    byte num = 0;
    for (int i = 0; i <= 7; i++) {
        num += m_pows[i] * bits[7 - i];
    }
    return num;
}

void Display64Led::resetPoints() {
    for (byte i = 0; i < 8; i++) {
        m_pointX[i] = 0;
        m_pointY[i] = 0;
    }
}
