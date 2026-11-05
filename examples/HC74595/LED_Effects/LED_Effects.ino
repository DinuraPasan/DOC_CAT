uint8_t SER = 10;     // Arduino pin connected to pin 14 (DS / data) of the 74HC595.
uint8_t RCLK = 11;    // Arduino pin connected to pin 12 (ST_CP / latch) of the 74HC595.
uint8_t SRCLK = 12;   // Arduino pin connected to pin 11 (SH_CP / clock) of the 74HC595.
uint8_t NUMOFIC = 2;  // Number of cascaded 74HC595 ICs.
uint8_t count = 5;    // Number of times to repeat each LED effect.

#include <DOC_CAT.h>
HC74595 Shift(NUMOFIC, SER, RCLK, SRCLK);

void setup() {}

void loop() {
  // Demonstrate manual output control using NoUpdate() and Update().
  // NoUpdate() changes the stored output state, while Update() applies it to the registers.
  for (byte i = 0; i <= count; i++) {
    for (byte j = 0; j <= count; j++) {
      Shift.NoUpdate(0, HIGH);  // Turn ON output 0.
      Shift.Update();
      delay(100);

      Shift.NoUpdate(0, LOW);  // Turn OFF output 0.
      Shift.Update();
      delay(100);
    }

    Shift.SetAll(true);  // Turn ON all outputs.
    delay(1000);
    Shift.SetAll(false);  // Turn OFF all outputs.
    delay(1000);
  }

  // Demonstrate LEDFlash() by flashing each output individually.
  // First sequence: outputs from lowest to highest.
  // Second sequence: outputs from highest to lowest.
  for (byte i = 0; i <= count; i++) {
    for (int j = 0; j < NUMOFIC * 8; j++) {
      Shift.LEDFlash(100, j);  // Syntax: LEDFlash(int duration, uint8_t pin).
    }

    for (int j = (NUMOFIC * 8) - 1; j >= 0; j--) {
      Shift.LEDFlash(100, j);
    }
  }

  // Demonstrate LEDSequence() by progressively turning ON and OFF outputs.
  // The sequence starts at the specified output and moves toward output 0.
  for (byte i = 0; i <= count; i++) {
    for (int j = 0; j < NUMOFIC * 8; j++) {
      Shift.LEDSequence(10, j);  // Syntax: LEDSequence(int duration, uint8_t pin).
    }
  }

  // Reverse the LED sequence direction by starting from the highest output.
  for (byte i = 0; i <= count; i++) {
    for (int j = (NUMOFIC * 8) - 1; j >= 0; j--) {
      Shift.LEDSequence(10, j);
    }
  }

  // Demonstrate LEDChase() with different output ranges and directions.
  // The reverse parameter selects descending (true) or ascending (false) order.
  Shift.LEDChase(count, 100, 0, (NUMOFIC * 8) - 1, true);
  Shift.LEDChase(count, 100, 0, (NUMOFIC * 8) - 1, false);
  Shift.LEDChase(count, 100, 1, 6, true);
  Shift.LEDChase(count, 100, 1, 6, false);

  // Alternate between ascending and descending LED chase effects.
  for (byte i = 0; i <= count; i++) {
    Shift.LEDChase(1, 100, 0, (NUMOFIC * 8) - 1, true);
    Shift.LEDChase(1, 100, 0, (NUMOFIC * 8) - 1, false);
  }

  // Demonstrate random LED effects within the specified output range.
  Shift.LEDRandomFlash(30, 100, 0, (NUMOFIC * 8) - 1);
  Shift.LEDRandomToggle(30, 100, 0, (NUMOFIC * 8) - 1);

  // Demonstrate mirrored LED effects using different output ranges and divisors.
  // The divisor controls how many outputs are activated from each end.
  Shift.LEDMirrorChase(count, 100, 0, (NUMOFIC * 8) - 1, 2);
  Shift.LEDMirrorChase(count, 100, 0, (NUMOFIC * 8) - 1, 3);
  Shift.LEDMirrorChase(count, 100, 2, 5, 2);
  Shift.LEDMirrorChase(count, 100, 2, 6, 3);
}