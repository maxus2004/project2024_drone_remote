#include <Arduino.h>

#include "controls.h"
#include "gui.h"
#include "radio.h"

Controls controls;

void setup() {
    Serial.begin(115200);

    controls_init();
    radio_init();

    Serial.end();

    gui_init();
    gui_ControlsPreview_start();
}

void loop() {
    controls_getControls(&controls);

    radio_sendControls(&controls);
    //gui_ControlsPreview_update(&controls);
}