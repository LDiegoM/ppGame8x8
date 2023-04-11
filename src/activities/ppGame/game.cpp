#include <activities/ppGame/game.h>

#include <common/activity.h>

//////////////////// Constructor
PPGame::PPGame(Display64Led* display, Joystick* joystick, PPGameLevel* gameLevel, GameScore* gameScore) {
    m_display = display;
    m_joystick = joystick;
    m_gameLevel = gameLevel;
    m_gameScore = gameScore;

    m_gameRunning = false;
}

//////////////////// Public methods implementation
String PPGame::className() {
    return "PPGame";
}

void PPGame::start() {
    startNewGame();
}

bool PPGame::loop() {
    if (!m_gameRunning)
        return false;

    m_playerPosition = m_joystick->getPosition();

    if (m_gameLevel->verifyLevelLimit()) {
        m_noActionCount++;
        if (m_noActionCount >= MAX_NO_ACTION_CYCLES) {
            // Player didn't do any action for last 5 cycles. Loses 1 point.
            m_gameScore->calculate(false);

            // Reset the no action counter
            m_noActionCount = 0;

            // Due to point decrement, the game may finish
            if (m_gameScore->gameEnd()) {
                endGame();
                return false;
            }
        }
        // Get a new random point
        m_randomPosition = getRandomPoint();
    }

    // Compose the image with player and random points
    composeGameDisplayImage();

    return true;
}

void PPGame::action() {
    m_gameScore->calculate(evaluateHitOrMiss());

    // Reset the no action counter
    m_noActionCount = 0;

    if (m_gameScore->gameEnd()) {
        endGame();
    } else {
        // Get a new random point
        m_randomPosition = getRandomPoint();

        // Reset the time count for the next random point
        m_gameLevel->restartLevel();
    }
}

//////////////////// Private methods implementation
void PPGame::startNewGame() {
    m_gameScore->reset();

    // Reset the no action counter
    m_noActionCount = 0;

    // Gets the first random point of the game
    m_randomPosition = getRandomPoint();

    m_display->resetDisplayImage();
    m_gameRunning = true;

    // Start the current level timer
    m_gameLevel->restartLevel();
}

void PPGame::endGame() {
    m_gameRunning = false;
}

displayPoint PPGame::getRandomPoint() {
    // Begin with an udesired point
    displayPoint point = {3, 3};
    while ((point.x == 3 && point.y == 3) ||
            (point.x == 3 && point.y == 4) ||
            (point.x == 4 && point.y == 3) ||
            (point.x == 4 && point.y == 4) ||
            (point.x == m_randomPosition.x && point.y == m_randomPosition.y)) {
        // Get random numbers for the point
        point.x = random(8);
        point.y = random(8);
    }
    return point;
}

bool PPGame::evaluateHitOrMiss() {
    return m_playerPosition.x == m_randomPosition.x && m_playerPosition.y == m_randomPosition.y;
}

void PPGame::composeGameDisplayImage() {
    for (byte x = 0; x < 8; x++) {
        for (byte y = 0; y < 8; y++) {
            if ((m_playerPosition.x == x && m_playerPosition.y == y) || 
                (m_randomPosition.x == x && m_randomPosition.y == y))
                m_display->setPixel(x, y, true);
            else
                m_display->setPixel(x, y, false);
        }
    }
}
