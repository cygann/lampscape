#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <lamp.h>

#define LED_PIN    6
#define LED_COUNT 80

int BUTTON_PWR = 13;
int BUTTON_SLT = 12;
int SPEAKER = 10;
bool lamp_on = false;

// Lamp lamp;
Lamp lamp(BUTTON_PWR, BUTTON_SLT, LED_PIN, LED_COUNT);
// Lamp lamp;

void setup() {

    Serial.begin(115200);

    pinMode(BUTTON_PWR, INPUT_PULLUP);
    pinMode(BUTTON_SLT, INPUT_PULLUP);
    pinMode(SPEAKER, OUTPUT);

    lamp.lamp_begin();

    // lamp = Lamp(BUTTON_PWR, BUTTON_SLT, LED_PIN, LED_COUNT);
}

void loop() {
    lamp.loop_turn();
}
