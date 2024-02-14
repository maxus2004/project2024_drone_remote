#pragma once

#include <stdint.h>

#include "controls.h"

#define RADIO_OFF 0
#define RADIO_FSK 1
#define RADIO_LORA 2
#define RADIO_FHSS 3

typedef struct __attribute__((__packed__)) {
    uint8_t radio1_mode;
    uint32_t radio1_frequency;
    uint8_t radio2_mode;
    uint32_t radio2_frequency;
} RadioSettings;

void radio_init();
void radio_setSettings(RadioSettings *settings);
void radio_sendSettings(RadioSettings *settings);
void radio_sendControls(Controls* controls);