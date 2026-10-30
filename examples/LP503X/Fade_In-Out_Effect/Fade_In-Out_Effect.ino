#include <DOC_CAT.h>

// Create an LP503X object with the device's I2C address.
LP503X ledDriver(0x30);

const uint8_t LED = 0;                   // Select the LED output to control (0–29 for LP5030, 0–35 for LP5036).
const uint8_t FADE_STEP = 5;             // Brightness change per update (higher values produce faster fading).
const unsigned long FADE_INTERVAL = 20;  // Time interval between brightness updates, in milliseconds.
uint8_t brightness = 0;                  // Current brightness level (0 = off, 255 = maximum brightness).
int8_t direction = 1;                    // Fade direction: 1 = increase brightness, -1 = decrease brightness.
unsigned long previousMillis = 0;        // Stores the time of the previous brightness update.

void setup() {
  // Initialize the LP503X device in normal operating mode.
  ledDriver.normal_mode();

  // Set the selected LED output's color-mixing level to maximum.
  // This example uses a single color channel; brightness is controlled separately.
  ledDriver.setColour(LED, 255);
}

void loop() {
  // Get the elapsed time since the Arduino started running.
  unsigned long currentMillis = millis();

  // Update brightness only when the specified interval has elapsed.
  // Using millis() avoids blocking other tasks with delay().
  if (currentMillis - previousMillis >= FADE_INTERVAL) {
    // Record the time of this update.
    previousMillis = currentMillis;

    // Increase or decrease brightness according to the current fade direction.
    brightness += direction * FADE_STEP;

    // Reverse direction when maximum brightness is reached.
    if (brightness >= 255) {
      brightness = 255;
      direction = -1;
    }
    // Reverse direction when minimum brightness is reached.
    else if (brightness <= 0) {
      brightness = 0;
      direction = 1;
    }

    // Apply the updated brightness to the selected LED output.
    ledDriver.setBrightness(LED, brightness);
  }
}