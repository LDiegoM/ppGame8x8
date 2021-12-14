#ifndef animation_h
#define animation_h

#include <Arduino.h>

struct animationPoint {
  bool value;
  byte x;
  byte y;
};

void beginAnimation();
void animateImage();

#endif
