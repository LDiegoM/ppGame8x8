#ifndef shiftRegisters_h
#define shiftRegisters_h

#include <Arduino.h>

class ShiftRegisters {
    private:
        byte m_pinShiftData;
        byte m_pinShiftClock;
        byte m_pinShiftRegister;

        byte m_shiftCount;
        byte* m_shiftValues;

    public:
        ShiftRegisters(byte pinShiftData, byte pinShiftClock, byte pinShiftRegister, byte shiftCount);

        void setShiftValue(byte shiftNumber, byte value);
        void sendValues();
};

#endif
