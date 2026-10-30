#include <DOC_CAT.h>

// Create an LP503X object with the device's I2C address.
LP503X ledDriver(0x30);

#define FADE_DELAY 10       // Delay between brightness updates (milliseconds).
#define MAX_BRIGHTNESS 255  // Maximum RGB color-mixing and brightness level.

void setup() {
  // Initialize the LP503X device in normal operating mode.
  ledDriver.normal_mode();

  // Enable RGB bank control for all 12 LED modules.
  for (uint8_t i = 0; i < 12; i++) {
    ledDriver.setModule(i, true);
  }
}

void loop() {
  // Gradually transition from red to green.
  for (int i = 0; i <= MAX_BRIGHTNESS; i++) {
    ledDriver.setRGBbank(255 - i, i, 0, MAX_BRIGHTNESS);
    delay(FADE_DELAY);
  }

  // Gradually transition from green to blue.
  for (int i = 0; i <= MAX_BRIGHTNESS; i++) {
    ledDriver.setRGBbank(0, 255 - i, i, MAX_BRIGHTNESS);
    delay(FADE_DELAY);
  }

  // Gradually transition from blue back to red.
  for (int i = 0; i <= MAX_BRIGHTNESS; i++) {
    ledDriver.setRGBbank(i, 0, 255 - i, MAX_BRIGHTNESS);
    delay(FADE_DELAY);
  }
}