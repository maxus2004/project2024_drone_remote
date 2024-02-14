#include "radio.h"

#include <Arduino.h>
#include <SX126x.h>

#define RF400_NRST 9
#define RF400_BUSY 8
#define RF400_NSS 10
#define RF400_TXEN 14
#define RF400_RXEN 15

#define RF900_NRST 6
#define RF900_BUSY 7
#define RF900_NSS 3
#define RF900_TXEN 5
#define RF900_RXEN 4

SX126x rf400;
SX126x rf900;

uint8_t rf400_mode = RADIO_LORA;
uint8_t rf900_mode = RADIO_LORA;

uint32_t packet_id = 0;

void radio_init() {
    pinMode(RF400_NSS, OUTPUT);
    pinMode(RF900_NSS, OUTPUT);
    digitalWrite(RF400_NSS, HIGH);
    digitalWrite(RF900_NSS, HIGH);

    if (!rf400.begin(RF400_NSS, RF400_NRST, RF400_BUSY, -1, RF400_TXEN,
                     RF400_RXEN)) {
        Serial.println("Something wrong, can't start 433Mhz radio");
        while (1) {}
    }
    Serial.println("initialized 433Mhz radio");
    rf400.setFrequency(433000000);
    rf400.setTxPower(10, SX126X_TX_POWER_SX1268);
    rf400.setLoRaModulation(7, 125000, 5, false);
    rf400.setSyncWord(0x3444);
    rf400.setLoRaPacket(LORA_HEADER_EXPLICIT, 12, 15, true, false);
    Serial.println("configured 433Mhz radio");

    if (!rf900.begin(RF900_NSS, RF900_NRST, RF900_BUSY, -1, RF900_TXEN,
                     RF900_RXEN)) {
        Serial.println("can't start 868Mhz radio");
        while (1) {}
    }
    Serial.println("initialized 868Mhz radio");
    rf900.setFrequency(868000000);
    rf900.setTxPower(10, SX126X_TX_POWER_SX1268);
    rf900.setLoRaModulation(7, 125000, 5, false);
    rf900.setSyncWord(0x3444);
    rf900.setLoRaPacket(LORA_HEADER_EXPLICIT, 12, 15, true, false);
    Serial.println("configured 868Mhz radio");
}

void radio_send(uint8_t type, void *data, uint8_t length) {
    if (rf400_mode != RADIO_OFF) {
        rf400.beginPacket();
        rf400.write((uint8_t *)&packet_id, sizeof(packet_id));
        rf400.write(type);
        rf400.write((uint8_t *)data, length);
        rf400.endPacket();
    }
    if (rf900_mode != RADIO_OFF) {
        rf900.beginPacket();
        rf900.write((uint8_t *)&packet_id, sizeof(packet_id));
        rf900.write(type);
        rf900.write((uint8_t *)data, length);
        rf900.endPacket();
    }

    rf400.wait();
    rf900.wait();

    packet_id++;
}

void radio_setSettings(RadioSettings *settings) {
    rf400.setFrequency(settings->radio1_frequency);
    switch (settings->radio1_mode) {
        case RADIO_OFF:
            rf400_mode = RADIO_OFF;
            break;
        case RADIO_FSK:
            rf400_mode = RADIO_FSK;
            rf400.setModem(FSK_MODEM);
            break;
        case RADIO_LORA:
            rf400_mode = RADIO_LORA;
            rf400.setModem(LORA_MODEM);
            break;
        case RADIO_FHSS:
            rf400_mode = RADIO_FHSS;
            rf400.setModem(FSK_MODEM);
            break;
    }
    rf900.setFrequency(settings->radio2_frequency);
    switch (settings->radio2_mode) {
        case RADIO_OFF:
            rf900_mode = RADIO_OFF;
            break;
        case RADIO_FSK:
            rf900_mode = RADIO_FSK;
            rf900.setModem(FSK_MODEM);
            break;
        case RADIO_LORA:
            rf900_mode = RADIO_LORA;
            rf900.setModem(LORA_MODEM);
            break;
        case RADIO_FHSS:
            rf900_mode = RADIO_FHSS;
            rf900.setModem(FSK_MODEM);
            break;
    }
}

void radio_sendSettings(RadioSettings *settings) {
    radio_send(0, settings, sizeof(RadioSettings));
}

void radio_sendControls(Controls *controls) {
    radio_send(1, controls, sizeof(Controls));
}