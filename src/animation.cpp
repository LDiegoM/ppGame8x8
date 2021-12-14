/*
    ppGame8x8 end game animation handling.

    Diego M. Lopez - 2021 (ldiegom@gmail.com)
*/

#include <animation.h>
#include <display64led.h>

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

animationPoint animationPoints[] = {
  {true, 0, 4}, {true, 1, 5}, {true, 1, 6}, {true, 3, 4}, {true, 2, 6}, {true, 3, 7},
  {true, 4, 7}, {true, 5, 6}, {true, 6, 6}, {true, 4, 4}, {true, 6, 5}, {true, 7, 4},
  {true, 7, 3}, {true, 6, 2}, {true, 6, 1}, {true, 4, 3}, {true, 5, 1}, {true, 4, 0},
  {true, 3, 0}, {true, 2, 1}, {true, 1, 1}, {true, 3, 3}, {true, 1, 2}, {true, 0, 3}
};
byte lenAnimationPoints = sizeof(animationPoints) / sizeof(animationPoint);
byte currentAnimationPoint = 0;

void beginAnimation() {
    resetDisplayImage();
    currentAnimationPoint = 0;
    for (byte i = 0; i < lenAnimationPoints; i++) {
        animationPoint* point = &animationPoints[i];
        point->value = true;
        displayImage[point->x][point->y] = 1;
    }
}

void animateImage() {
  animationPoint* point = &animationPoints[currentAnimationPoint];
  point->value = !point->value;
  displayImage[point->x][point->y] = (point->value ? 1 : 0);

  currentAnimationPoint++;
  if (currentAnimationPoint >= lenAnimationPoints) {
    currentAnimationPoint = 0;
  }
}
