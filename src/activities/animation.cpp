/*
    ppGame8x8 end game animation handling.

    Diego M. Lopez - 2021 (ldiegom@gmail.com)
*/

#include <activities/animation.h>

/* This represents the initial animation image
{0, 0, 0, 1, 1, 0, 0, 0}
{0, 1, 1, 0, 0, 1, 1, 0}
{0, 1, 0, 0, 0, 0, 1, 0}
{1, 0, 0, 1, 1, 0, 0, 1}
{1, 0, 0, 1, 1, 0, 0, 1}
{0, 1, 0, 0, 0, 0, 1, 0}
{0, 1, 1, 0, 0, 1, 1, 0}
{0, 0, 0, 1, 1, 0, 0, 0}
*/

//////////////////// Constructor
Animation::Animation(Display64Led* display) {
    m_animationTimer = new Timer(40);
    m_display = display;
}

//////////////////// Public methods implementation
String Animation::className() {
    return "Animation";
}

void Animation::start() {
    m_display->resetDisplayImage();
    m_currentAnimationPoint = 0;
    for (byte i = 0; i < lenAnimationPoints; i++) {
        animationPoint* point = &animationPoints[i];
        point->value = true;
        m_display->setPixel(point->x, point->y, point->value);
    }
    m_animationTimer->start();
}

bool Animation::loop() {
    if (!m_animationTimer->isRunning())
        return false;

    if (m_animationTimer->isTime())
        animateImage();

    return true;
}

void Animation::action() {
    m_animationTimer->stop();
}

//////////////////// Private methods implementation
void Animation::animateImage() {
    animationPoint* point = &animationPoints[m_currentAnimationPoint];
    point->value = !point->value;
    m_display->setPixel(point->x, point->y, point->value);

    m_currentAnimationPoint++;
    if (m_currentAnimationPoint >= lenAnimationPoints)
        m_currentAnimationPoint = 0;
}
