#include "FastLED.h"

#define LEDS1_NUM 25
#define LEDS1_PIN 11

#define LEDS2_NUM 40
#define LEDS2_PIN 14

#define LEDS_SATURATION 160
#define LEDS_BRIGHTNESS 128

CRGB leds[LEDS1_NUM + LEDS2_NUM];
byte hueCurrent = 0;
byte hueDestination = 0;
char hueStep = 5;

#define UPDATE_DELAY 50

void setup() {
  FastLED.addLeds<WS2801, LEDS1_PIN, 13, RGB>(leds, 0, LEDS1_NUM);
  FastLED.addLeds<WS2811, LEDS2_PIN, RGB>(leds, LEDS1_NUM, LEDS2_NUM);
  // Adjust data rate if you have issues: 0-fast, 7-slow
  //FastLED.setDataRate(3);
  
  for (int ii=0; ii< (LEDS1_NUM + LEDS2_NUM); ii++) {
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
  delay(UPDATE_DELAY);
}

void pushLed(byte hueValue) {
  for (int ii=0; ii<(LEDS1_NUM + LEDS2_NUM - 1); ii++) {
    leds[ii] = leds[ii+1];
  }
  leds[LEDS1_NUM + LEDS2_NUM - 1].setHSV(hueValue, LEDS_SATURATION, LEDS_BRIGHTNESS);
}
