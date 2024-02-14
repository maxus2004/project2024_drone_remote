#include "controls.h"

#include <Arduino.h>

void controls_init(){
    pinMode(A2, INPUT);
    pinMode(A3, INPUT);
    pinMode(A6, INPUT);
    pinMode(A7, INPUT);
    pinMode(A4, INPUT_PULLUP);
    pinMode(A5, INPUT_PULLUP);
    pinMode(1, INPUT_PULLUP);
}

void controls_getControls(Controls* controls) {
    controls->x1 = (255 - (analogRead(A3) >> 2));
    controls->y1 = (analogRead(A2) >> 2);
    controls->x2 = (255 - (analogRead(A7) >> 2));
    controls->y2 = (analogRead(A6) >> 2);
    controls->b1 = !digitalRead(1);
    controls->b2 = !digitalRead(A4);
    controls->b3 = !digitalRead(A5);
}