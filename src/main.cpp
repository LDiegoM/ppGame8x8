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

const byte pinShiftData     = 3;  // Pin conectado a DS pin 14 de 74HC595
const byte pinShiftClock    = 4;  // Pin conectado a SHCP pin 11 de 74HC595
const byte pinShiftRegister = 5;  // Pin conectado a STCP pin 12 de 74HC595
ShiftRegisters* shiftRegisters;

// The joystick is composed by 2 potentiometers
const byte pinJoystickX = A0;
const byte pinJoystickY = A1;

// The game button is connected to a pin that supports interruption
const byte pinButton = 2;

// Use a disconnected analog pin to seed the random sequence
const byte pinAnalogForRandomSeed = A2;

Display64Led* display;
Timer* animationTimer;

// Game scopre handling
GameScore* gameScore;

displayPoint playerPosition, randomPosition;

 // Joystick handling
int joystickXValue;
int joystickYValue;

// Button handling, avoiding bounce and sticky conditions
Button* button;

// Implements 3 game levels
Timer* levelTimers[] = {
  new Timer(2000, ULONG_MAX, millis),
  new Timer(1250, ULONG_MAX, millis),
  new Timer(800, ULONG_MAX, millis)
};
byte currentLevel;
byte levelCount = sizeof(levelTimers) / sizeof(Timer*);
Timer* levelTimer;
bool levelChanged = false;

bool gameRunning;

// Handle no action made by player. If player doesn't press the button for 5 cycles, loses 1 point
const byte MAX_NO_ACTION_CYCLES = 5;
byte noActionCount;

void startNewGame();
void endGame();
void buttonPressed();
void calculateScoreAndLevel(bool pointWon);
displayPoint getRandomPoint();
bool evaluateHitOrMiss();

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
    gameScore = new GameScore(shiftRegisters, 0);
    display = new Display64Led(shiftRegisters, 1, 2);
    button = new Button(pinButton, buttonPressed);

    gameRunning = false;

    gameScore->showNewScore(currentScore);
    beginAnimation();
    animationTimer = new Timer(40, ULONG_MAX, millis);
    animationTimer->start();
}

void loop() {
    button->check();

    if (!gameRunning) {
        if (animationTimer->isTime()) {
            animateImage();
        }
    } else {
        // Game is running

        joystickXValue = analogRead(pinJoystickX);
        playerPosition.x = map(joystickXValue, 0, 1024, 0, 8);

        joystickYValue = analogRead(pinJoystickY);
        playerPosition.y = map(joystickYValue, 0, 1024, 0, 8);

        if (levelTimer->isTime()) {
            noActionCount++;
            if (noActionCount >= MAX_NO_ACTION_CYCLES) {
                calculateScoreAndLevel(false);

                // Reset the no action counter
                noActionCount = 0;

                // Due to point decrement, the game may finish
                if (!gameRunning)
                    return;

                if (levelChanged)
                    levelTimer->start();
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
    // Game starts with score = 3
    currentScore = STARTING_SCORE;
    gameScore->showNewScore(currentScore);

    // Choose the easier game level
    currentLevel = 1;
    levelTimer = levelTimers[currentLevel - 1];
    levelChanged = false;

    noActionCount = 0;

    // Gets the first random point of the game
    randomPosition = getRandomPoint();

    animationTimer->stop();
    resetDisplayImage();
    gameRunning = true;

    // Start the current level timer
    levelTimer->start();
}

void endGame() {
    levelTimer->stop();
    gameRunning = false;
    beginAnimation();
    animationTimer->start();
}

void buttonPressed() {
    if (!gameRunning) {
        startNewGame();
    } else {
        calculateScoreAndLevel(evaluateHitOrMiss());

        noActionCount = 0;

        // Get a new random point
        randomPosition = getRandomPoint();
        levelTimer->start();
    }
}

void calculateScoreAndLevel(bool pointWon) {
    if (pointWon)
        currentScore++;
    else
        currentScore--;

    if (currentScore == 0) {
        currentLevel--;
        levelChanged = true;
    } else if (currentScore > 9) {
        currentLevel++;
        levelChanged = true;
    } else {
        levelChanged = false;
    }

    if (levelChanged) {
        levelTimer->stop();
        currentScore = STARTING_SCORE;

        if (currentLevel <= 0) {
            currentScore = 0;
            gameScore->showNewScore(currentScore);
            gameScore->showScoreLed(pointWon);
            endGame();
            return;
        } else if (currentLevel > levelCount) {
            currentScore = levelCount;
            gameScore->showNewScore(currentScore);
            gameScore->showScoreLed(pointWon);
            endGame();
            return;
        }

        levelTimer = levelTimers[currentLevel - 1];
    }
    gameScore->showNewScore(currentScore);
    gameScore->showScoreLed(pointWon);
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
