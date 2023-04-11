/*
    ppGame8x8 shift registers handling.

    This class is a handler to send values to N ics 74HC595.
    For the game is configured with 3 shift registers:
    - 0: point with 7 segment display and luminic signals.
    - 1: 8x8 display cathodes
    - 2: 8x8 display anodes

    Diego M. Lopez - 2021 (ldiegom@gmail.com)
*/

#include <platform/shiftRegisters.h>

ShiftRegisters::ShiftRegisters(byte pinShiftData, byte pinShiftClock, byte pinShiftRegister,
                               byte shiftCount) {
    // Set shift registers pins as OUTPUT
    pinMode(pinShiftRegister, OUTPUT);
    pinMode(pinShiftClock, OUTPUT);
    pinMode(pinShiftData, OUTPUT);
    digitalWrite(pinShiftRegister, LOW);

    m_pinShiftData = pinShiftData;
    m_pinShiftClock = pinShiftClock;
    m_pinShiftRegister = pinShiftRegister;
    m_shiftCount = shiftCount;

    m_shiftValues = new byte[shiftCount];
    for (byte n = 0; n < shiftCount; n++)
        m_shiftValues[n] = 0;
}

void ShiftRegisters::setShiftValue(byte shiftNumber, byte value) {
    m_shiftValues[shiftNumber] = value;
}

void ShiftRegisters::sendValues() {
    for (byte i = 0; i < m_shiftCount; i++) {
        shiftOut(m_pinShiftData, m_pinShiftClock, MSBFIRST, m_shiftValues[i]);
    }

    // Send the data to output register
    digitalWrite(m_pinShiftRegister, HIGH);
    digitalWrite(m_pinShiftRegister, LOW);
}
