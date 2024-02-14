#pragma once

#include <stdint.h>

typedef struct __attribute__((__packed__)){
    uint8_t x1;
    uint8_t y1;
    uint8_t x2;
    uint8_t y2;
    uint8_t b1 : 1;
    uint8_t b2 : 1;
    uint8_t b3 : 1;
} Controls;

void controls_init();
void controls_getControls(Controls* controls);