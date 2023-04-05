/*
    ppGame8x8 main program

    Diego M. Lopez - 2021 (ldiegom@gmail.com)
*/

#include <Arduino.h>
#include <limits.h>

#include <shiftRegisters.h>
#include <display64led.h>
#include <timer.h>
#include <animation.h>
#include <gameScore.h>
#include <button.h>

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

// End game animation handling
Animation* animation;

// Game scopre handling
GameScore* gameScore;

// Button handling, avoiding bounce and sticky conditions
Button* button;

displayPoint playerPosition, randomPosition;

bool gameRunning;

// Handle no action made by player. If player doesn't press the button for 5 cycles, loses 1 point
const byte MAX_NO_ACTION_CYCLES = 5;
byte noActionCount;

void startNewGame();
void endGame();
void buttonPressed();
displayPoint getRandomPoint();
bool evaluateHitOrMiss();
void composeGameDisplayImage(displayPoint playerPosition, displayPoint randomPosition);

void setup() {
    Serial.begin(9600);

    // Set shift registers pins as OUTPUT
    pinMode(pinShiftRegister, OUTPUT);
    pinMode(pinShiftClock, OUTPUT);
    pinMode(pinShiftData, OUTPUT);
    digitalWrite(pinShiftRegister, LOW);

    // If analog input pin 2 is unconnected, random analog noise will cause the call to randomSeed()
    // to generate different seed numbers each time the sketch runs.
    // randomSeed() will then shuffle the random function.
    randomSeed(analogRead(pinAnalogForRandomSeed));

    shiftRegisters = new ShiftRegisters(pinShiftData, pinShiftClock, pinShiftRegister, 3);
    gameScore = new GameScore(shiftRegisters, 0, pinBuzzer);
    display = new Display64Led(shiftRegisters, 1, 2);
    button = new Button(pinButton, buttonPressed);
    animation = new Animation(display);

    gameRunning = false;

    animation->start();
}

void loop() {
    button->check();

    if (!gameRunning) {
        animation->refresh();
    } else {
        // Game is running

        playerPosition.x = map(analogRead(pinJoystickX), 0, 1024, 0, 8);
        playerPosition.y = map(analogRead(pinJoystickY), 0, 1024, 0, 8);

        if (levelTimer->isTime()) {
            noActionCount++;
            if (noActionCount >= MAX_NO_ACTION_CYCLES) {
                // Player didn't do any action for last 5 cycles. Loses 1 point.
                gameScore->calculateScoreAndLevel(false);

                // Reset the no action counter
                noActionCount = 0;

                // Due to point decrement, the game may finish
                if (gameScore->gameEnd()) {
                    endGame();
                    return;
                }
            }
            // Get a new random point
            randomPosition = getRandomPoint();
        }

        // Compose the image with player and random points
        composeGameDisplayImage(playerPosition, randomPosition);
    }

    gameScore->refresh();
    display->refresh();
}

void startNewGame() {
    gameScore->resetScoreAndLevel();

    // Reset the no action counter
    noActionCount = 0;

    // Gets the first random point of the game
    randomPosition = getRandomPoint();

    animation->stop();
    display->resetDisplayImage();
    gameRunning = true;

    // Start the current level timer
    levelTimer->start();
}

void endGame() {
    gameRunning = false;
    animation->start();
}

void buttonPressed() {
    if (!gameRunning) {
        startNewGame();
    } else {
        gameScore->calculateScoreAndLevel(evaluateHitOrMiss());

        // Reset the no action counter
        noActionCount = 0;

        if (gameScore->gameEnd()) {
            endGame();
        } else {
            // Get a new random point
            randomPosition = getRandomPoint();

            // Reset the time count for the next random point
            levelTimer->start();
        }
    }
}

displayPoint getRandomPoint() {
    // Begin with an udesired point
    displayPoint point = {3, 3};
    while ((point.x == 3 && point.y == 3) ||
            (point.x == 3 && point.y == 4) ||
            (point.x == 4 && point.y == 3) ||
            (point.x == 4 && point.y == 4) ||
            (point.x == randomPosition.x && point.y == randomPosition.y)) {
        // Get random numbers for the point
        point.x = random(8);
        point.y = random(8);
    }
    return point;
}

bool evaluateHitOrMiss() {
    return playerPosition.x == randomPosition.x && playerPosition.y == randomPosition.y;
}

void composeGameDisplayImage(displayPoint playerPosition, displayPoint randomPosition) {
    for (byte x = 0; x < 8; x++) {
        for (byte y = 0; y < 8; y++) {
            if ((playerPosition.x == x && playerPosition.y == y) || 
                (randomPosition.x == x && randomPosition.y == y))
                display->setPixel(x, y, true);
            else
                display->setPixel(x, y, false);
        }
    }
}
