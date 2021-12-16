/*
    ppGame8x8 end game animation handling.

    Diego M. Lopez - 2021 (ldiegom@gmail.com)
*/

#include <animation.h>
#include <display64led.h>
#include <limits.h>

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
Animation::Animation() {
    m_animationTimer = new Timer(40, ULONG_MAX, millis);
}

//////////////////// Public methods implementation
void Animation::start() {
    resetDisplayImage();
    m_currentAnimationPoint = 0;
    for (byte i = 0; i < lenAnimationPoints; i++) {
        animationPoint* point = &animationPoints[i];
        point->value = true;
        displayImage[point->x][point->y] = 1;
    }
    m_animationTimer->start();
}

void Animation::refresh() {
    if (m_animationTimer->isTime())
        animateImage();
}

void Animation::stop() {
    m_animationTimer->stop();
}

//////////////////// Private methods implementation
void Animation::animateImage() {
    animationPoint* point = &animationPoints[m_currentAnimationPoint];
    point->value = !point->value;
    displayImage[point->x][point->y] = (point->value ? 1 : 0);

    m_currentAnimationPoint++;
    if (m_currentAnimationPoint >= lenAnimationPoints)
        m_currentAnimationPoint = 0;
}
