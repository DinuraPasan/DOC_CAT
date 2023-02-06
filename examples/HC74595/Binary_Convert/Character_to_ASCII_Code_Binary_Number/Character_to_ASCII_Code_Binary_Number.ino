//  Produced by Dinura Pasan in February 2023 and distributed free of charge.
//  Controlling the 74HC595 shift registers IC from within the Arduino environment.
//  Source Code --> https://github.com/DinuraPasan/DOC_CAT/
//  Convert to character ASCII code number and ASCII number to binary.

uint8_t SER = 10;     // pin 14 on the 74HC595  outher name DS pin(data pin)
uint8_t RCLK = 11;    // pin 12 on the 74HC595  outher name ST_CP pin(latch pin)
uint8_t SRCLK = 12;   // pin 11 on the 74HC595  outher name SH_CP pin(clock pin)
uint8_t NUMOFIC = 2;  // Number of IC
uint8_t ReadPin = 2;  // Digital read pin

#include <DOC_CAT.h>
HC74595 Shift(NUMOFIC, SER, RCLK, SRCLK);

void setup() {
  Serial.begin(9600);
  pinMode(ReadPin, INPUT);
}

void loop() {
  if (Serial.available()) {
    char c = Serial.read();
    if (digitalRead(ReadPin) == HIGH) {
      Shift.CharacterToBinary(c, true);  // Syntax(char Character, boolean(Left or Right));
      delay(100);
    } else {
      Shift.CharacterToBinary(c, false);
      delay(100);
    }
  }
}