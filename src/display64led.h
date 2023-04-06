#ifndef display64led_h
#define display64led_h

#include <Arduino.h>
#include <shiftRegisters.h>

struct displayPoint {
    byte x;
    byte y;
};

class Display64Led {
    private:
        byte m_displayImage[8][8] = {
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
        };
        byte m_pointX[8];
        byte m_pointY[8];

        // This is a display conected to two 74HC595 ics (shift registers).
        ShiftRegisters* m_shiftRegisters;
        // On high shift has the displays leds cathodes.
        // Theese pins are set to 0 to be used as GND for leds.
        // When theese pins are LOW, the leds may be turned ON.
        byte m_shiftRegisterHigh;
        // On low shift has the displays leds anodes.
        byte m_shiftRegisterLow;

        // Used to calculate a decimal value from it's binary representation.
        const byte m_pows[8] = {1, 2, 4, 8, 16, 32, 64, 128};
        
        byte decFromBin(byte bits[8]);
        void resetPoints();

    public:
        Display64Led(ShiftRegisters* shiftRegisters, byte shiftRegisterHigh, byte shiftRegisterLow);

        void refresh();
        void resetDisplayImage();
        void setPixel(byte x, byte y, bool on);
};

#endif
