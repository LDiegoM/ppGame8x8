#include <activities/tetris/game.h>

//////////////////// Constructor
Tetris::Tetris(Display64Led* display, Joystick* joystick, TetrisLevel* gameLevel, GameScore* gameScore) {
    m_display = display;
    m_joystick = joystick;
    m_gameLevel = gameLevel;
    m_gameScore = gameScore;

    m_animation = new TetrisAnimation(m_display);
    m_gameRunning = false;
}

//////////////////// Public methods implementation
String Tetris::className() {
    return "Tetris";
}

void Tetris::start() {
    m_gameRunning = true;

    m_display->resetDisplayImage();
    m_gameLevel->restartLevel();
}

bool Tetris::loop() {
    if (!m_gameRunning)
        return false;

    if (m_animation->isRunning()) {
        m_animation->refresh();

        if (!m_animation->isRunning())
            return false;
    }

    m_joystickPosition = m_joystick->getPosition();
    // TODO: Evaluate if joystick moed left or right.
        // TODO: If joystick moved, move current shape one space left or right.

    if (m_gameLevel->verifyLevelLimit()) {
        // TODO: If shape is currently at bottom possible line.
            // TODO: Evaluate if a line was filled.
                // TODO: If a line/s was/were filled, remove filled line/s and drop down upper lines.
                // TODO: Each 2 filled, increment 1 point.

            // TODO: Evaluate if shape remains in the upper line.
                // TODO: If shape is still in the upper line, end game and return false.

            // TODO: Randomize next shape and draw it at upper line.
        // TODO: Else (shape is not at bottom possible line).
            // TODO: Pull shap one line down.
    }

    // Compose the image with player and random points
    composeGameDisplayImage();

    return true;
}

void Tetris::action() {
    // TODO: Drop down current shape in current X position.

    // TODO: Evaluate if shape remains in the upper line.
        // TODO: If shape is still in the upper line, end game.
    

    // Just for test porpuses.
    m_animation->start();
}

//////////////////// Private methods implementation
void Tetris::composeGameDisplayImage() {
}
