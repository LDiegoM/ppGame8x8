# About

PP Game 8x8 is a game developed for Arduino Uno with Atmega328P.

It was developed using PaltformIO with Visual Studio Code.

The game consists in a point and catch, using the joystick to catch randomly positioned points by pressing the touch switch.

In [this document](./doc/README.md) you´ll find the electronic details to assemble this project.

# Rules

The game starts with 3 points. When player hits the random point gains 1 point. When player miss, then loses 1 point.

When the score reaches 9 point, it will reset to 3 points, and increase 1 level. Game has 3 levels. Afther winning the third level, game will end.

When the score reaches 0 point, it will reset to 3 points reaching back to previous level. If loss the level 1, then the game will end.

Note that if player doesn't do any action during 5 random cycles, the game will consider 1 point lost.

# Authors

- Main idea by Diego M. Lopez (ldiegom@gmail.com)

- Prototype electronic assemble and testing: Joaquin Ignacio Lopez

# Changelog

## 1.1.0 - 20/12/2021

- Add sound indicator for scoring system.

## 1.0.0 - 15/12/2021

- Refactor animation component.
- Refactor GameScore component to hide public methods.

## 0.0.2 - 14/12/2021

- Add 3 leds to indicate current level.
- Refactor GameScore class to implement current level indicator logic.
- Update the documentation according to needed electronic changes.

## 0.0.1 - 10/12/2021

- First code revision of the game.
