#include "FastLED.h"

#define LEDS_NUM 4
#define LEDS_PIN 12
#define LEDS_SATURATION 32
#define LEDS_BRIGHTNESS 96

CRGB leds[LEDS_NUM];
byte hueCurrent = 0;
byte hueDestination = 0;
char hueStep = 1;

void setup() {
  FastLED.addLeds<NEOPIXEL, LEDS_PIN>(leds, LEDS_NUM);
  for (int ii=0; ii<LEDS_NUM; ii++) {
    leds[ii] = CHSV(hueCurrent, LEDS_SATURATION, LEDS_BRIGHTNESS);
  }
  randomSeed(analogRead(0));
}

void loop() {
  if (abs(hueCurrent - hueDestination) < hueStep) {
    hueDestination = random(255);
    hueStep = ((hueCurrent < hueDestination) && (hueStep < 0)) ? hueStep : -hueStep;
  }
  hueCurrent += hueStep;
  pushLed(hueCurrent);
  FastLED.show();
  delay(100);
}

void pushLed(byte hueValue) {
  for (int ii=0; ii<(LEDS_NUM-1); ii++) {
    leds[ii] = leds[ii+1];
  }
  leds[LEDS_NUM-1].setHSV(hueValue, LEDS_SATURATION, LEDS_BRIGHTNESS);
}
