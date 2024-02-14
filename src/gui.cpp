#include "gui.h"

#include <Ucglib.h>

#define DISPLAY_DC 0
#define DISPLAY_CS 2

Ucglib_ST7735_18x128x160_HWSPI display(DISPLAY_DC, DISPLAY_CS);

void gui_init() {
    display.begin(UCG_FONT_MODE_TRANSPARENT);
    display.setRotate90();
    display.setColor(255, 255, 255);
    display.drawBox(0, 22, 160, 80);

    display.setFont(ucg_font_8x13_tr);
}

void gui_ControlsPreview_start() {
    display.setColor(0, 0, 0);
    display.setPrintPos(1, 31 + 16 * 0);
    display.print("X1: ");
    display.setPrintPos(1, 31 + 16 * 1);
    display.print("Y1: ");
    display.setPrintPos(1, 31 + 16 * 2);
    display.print("B1: ");
    display.setPrintPos(95, 31 + 16 * 0);
    display.print("X2: ");
    display.setPrintPos(95, 31 + 16 * 1);
    display.print("Y2: ");
    display.setPrintPos(95, 31 + 16 * 2);
    display.print("B2: ");
    display.setPrintPos(50, 22 + 9 + 14 * 3);
    display.print("B3: ");
}

void gui_ControlsPreview_update(Controls* controls){
    display.setColor(255, 255, 255);
    display.drawBox(33, 22, 24, 41);
    display.setColor(0, 0, 0);

    display.setPrintPos(33, 31 + 16 * 0);
    display.print(controls->x1);

    display.setPrintPos(33, 31 + 16 * 1);
    display.print(controls->y1);

    display.setPrintPos(33, 31 + 16 * 2);
    display.print(controls->b1);

    display.setColor(255, 255, 255);
    display.drawBox(127, 22, 24, 41);
    display.setColor(0, 0, 0);

    display.setPrintPos(127, 31 + 16 * 0);
    display.print(controls->x2);

    display.setPrintPos(127, 31 + 16 * 1);
    display.print(controls->y2);

    display.setPrintPos(127, 31 + 16 * 2);
    display.print(controls->b2);

    display.setColor(255, 255, 255);
    display.drawBox(82, 22 + 14 * 3, 8, 16);
    display.setColor(0, 0, 0);

    display.setPrintPos(82, 31 + 14 * 3);
    display.print(controls->b3);
}