/*
    ppGame8x8 main program

    Diego M. Lopez - 2021 (ldiegom@gmail.com)
*/

#include <platform/shiftRegisters.h>
#include <platform/display64led.h>
#include <platform/timer.h>
#include <platform/button.h>
#include <platform/joystick.h>
#include <common/gameScore.h>
#include <activities/animation.h>
#include <activities/selector.h>
#include <activities/ppGame/level.h>
#include <activities/ppGame/game.h>
#include <activities/paint/level.h>
#include <activities/paint/paint.h>

const byte pinShiftData     = 3;  // Pin connected to SER   pin 14 de 74HC595
const byte pinShiftClock    = 4;  // Pin connected to SRCLK pin 11 de 74HC595
const byte pinShiftRegister = 5;  // Pin connected to RCLK  pin 12 de 74HC595
ShiftRegisters* shiftRegisters;

// The joystick is composed by 2 potentiometers
const byte pinJoystickX = A0;
const byte pinJoystickY = A1;

// The game button is connected to a pin that supports interruption
const byte pinButton = 2;

// Use a disconnected analog pin to seed the random sequence
const byte pinAnalogForRandomSeed = A2;

// The scoring sound indicator is connected to a PWM pin
const byte pinBuzzer = 6;

// Display 8x8 handling
Display64Led* display;

// Button handling, avoiding bounce and sticky conditions
Button* button;

// Joystick handling
Joystick* joystick;

// End game animation handling
Animation* animation;

// Activity selection handling
Selector* selector;

// Game level handling
PPGameLevel* ppGameLevel;

// Game score handling
GameScore* ppGameScore;

PPGame* ppGame;

PaintLevel* paintLevel;
GameScore* paintScore;
Paint* paint;

Activity* currentActivity;
Activity* previousActivity;

void buttonPressed();

void setup() {
    Serial.begin(9600);

    // If analog input pin 2 is unconnected, random analog noise will cause the call to randomSeed()
    // to generate different seed numbers each time the sketch runs.
    // randomSeed() will then shuffle the random function.
    randomSeed(analogRead(pinAnalogForRandomSeed));

    // Platform objects initialization.
    shiftRegisters = new ShiftRegisters(pinShiftData, pinShiftClock, pinShiftRegister, 3);
    display = new Display64Led(shiftRegisters, 1, 2);
    button = new Button(pinButton, buttonPressed);
    joystick = new Joystick(pinJoystickX, pinJoystickY);

    animation = new Animation(display);

    selector = new Selector(display, joystick);

    ppGameLevel = new PPGameLevel();
    ppGameScore = new GameScore(ppGameLevel, shiftRegisters, 0, pinBuzzer, 3);
    ppGame = new PPGame(display, joystick, ppGameLevel, ppGameScore);

    paintLevel = new PaintLevel();
    paintScore = new GameScore(paintLevel, shiftRegisters, 0, pinBuzzer, 0);
    paint = new Paint(display, joystick, paintLevel, paintScore);

    animation->addNextActivity(selector);
    selector->addNextActivity(animation);
    selector->addNextActivity(ppGame);
    selector->addNextActivity(paint);
    ppGame->addNextActivity(animation);
    paint->addNextActivity(animation);

    currentActivity = animation;
    previousActivity = currentActivity;

    animation->start();
}

void loop() {
    button->check();

    if (!currentActivity->loop()) {
        previousActivity = currentActivity;
        currentActivity = currentActivity->getNextActivity();
        if (currentActivity == NULL)
            currentActivity = animation;
        currentActivity->start();
    }

    if ((currentActivity->className().equals("PPGame")) || 
        (currentActivity->className().equals("Animation") && previousActivity->className().equals("PPGame")))
        ppGameScore->refresh();

    if ((currentActivity->className().equals("Paint")) ||
        (currentActivity->className().equals("Animation") && previousActivity->className().equals("Paint")))
        paintScore->refresh();

    display->refresh();
}

void buttonPressed() {
    currentActivity->action();
}
