//  Produced by Dinura Pasan in February 2023 and distributed free of charge.
//  Controlling the 74HC595 shift registers IC from within the Arduino environment.
//  Source Code --> https://github.com/DinuraPasan/DOC_CAT/
//  Doing the same thing at several location.

uint8_t SER = 10;                      // pin 14 on the 74HC595  outher name DS pin(data pin)
uint8_t RCLK = 11;                     // pin 12 on the 74HC595  outher name ST_CP pin(latch pin)
uint8_t SRCLK = 12;                    // pin 11 on the 74HC595  outher name SH_CP pin(clock pin)
uint8_t NUMOFIC = 2;                   // Number of IC
int data[] = { 0, 4, 6, 12, 15, 18 };  // defing Location array

#include <DOC_CAT.h>
HC74595 Shift(NUMOFIC, SER, RCLK, SRCLK);

void setup() {}

void loop() {
  Shift.Location(HIGH, 0, data);  // Syntax(boolean valve, int pin, int location array)
  Shift.Location(HIGH, 1, data);
  delay(100);
  Shift.Location(LOW, 1, data);
  delay(100);
}