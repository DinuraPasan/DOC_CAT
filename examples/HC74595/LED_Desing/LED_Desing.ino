//  Produced by Dinura Pasan in February 2023 and distributed free of charge.
//  Controlling the 74HC595 shift registers IC from within the Arduino environment.
//  Source Code --> https://github.com/DinuraPasan/DOC_CAT/
//  Simple LED design.

uint8_t SER = 10;     // pin 14 on the 74HC595  outher name DS pin(data pin)
uint8_t RCLK = 11;    // pin 12 on the 74HC595  outher name ST_CP pin(latch pin)
uint8_t SRCLK = 12;   // pin 11 on the 74HC595  outher name SH_CP pin(clock pin)
uint8_t NUMOFIC = 2;  // Number of IC
uint8_t count = 5;    // Loop Count

#include <DOC_CAT.h>
HC74595 Shift(NUMOFIC, SER, RCLK, SRCLK);

void setup() {}

void loop() {
  for (byte i = 0; i <= count; i++) {
    for (byte i = 0; i <= count; i++) {
      Shift.NoUpdate(0, HIGH);  // Syntax(int pin,boolean valve)
      Shift.Update();
      delay(100);
      Shift.NoUpdate(0, LOW);
      Shift.Update();
      delay(100);
    }
    Shift.SetAll(true);  // set all pin High
    delay(1000);
    Shift.SetAll(false);  // set all pin Low
    delay(1000);
  }

  for (byte i = 0; i <= count; i++) {
    for (int i = 0; i <= (NUMOFIC * 8) - 1; i++) {
      Shift.LEDdesing1(100, i);  // Syntax(int delay, uint8_t pin)
    }
    for (int i = (NUMOFIC * 8) - 1; i >= 0; i--) {
      Shift.LEDdesing1(100, i);
    }
  }
  for (byte i = 0; i <= count; i++) {
    for (int i = 0; i <= (NUMOFIC * 8) - 1; i++) {
      Shift.LEDdesing2(10, i);  // Syntax(int delay, uint8_t pin)
    }
  }
  for (byte i = 0; i <= count; i++) {
    for (int i = (NUMOFIC * 8) - 1; i >= 0; i--) {
      Shift.LEDdesing2(10, i);
    }
  }
  Shift.LEDdesing3(count, 100, 0, NUMOFIC * 8, true);  // Syntax(uint8_t count, int delay, uint8_t Min, uint8_t Max, bool type)
  Shift.LEDdesing3(count, 100, 0, NUMOFIC * 8, false);
  Shift.LEDdesing3(count, 100, 1, 6, true);
  Shift.LEDdesing3(count, 100, 1, 6, false);
  for (byte i = 0; i <= count; i++) {
    Shift.LEDdesing3(1, 100, 0, NUMOFIC * 8, true);
    Shift.LEDdesing3(1, 100, 0, NUMOFIC * 8, false);
  }
  Shift.LEDdesing4(30, 100, 0, NUMOFIC * 8);        // Syntax(uint8_t count, int delay, uint8_t Min, uint8_t Max)
  Shift.LEDdesing5(30, 100, 0, NUMOFIC * 8);        // Syntax(uint8_t count, int delay, uint8_t Min, uint8_t Max)
  Shift.LEDdesing6(count, 100, 0, NUMOFIC * 8, 2);  // Syntax(uint8_t count, int delay, uint8_t Min, uint8_t Max, uint8_t devide)
  Shift.LEDdesing6(count, 100, 0, NUMOFIC * 8, 3);
  Shift.LEDdesing6(count, 100, 2, 5, 2);
  Shift.LEDdesing6(count, 100, 2, 6, 3);
}