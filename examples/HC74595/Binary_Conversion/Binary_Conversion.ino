uint8_t SER = 10;     // Arduino pin connected to pin 14 (DS / data) of the 74HC595.
uint8_t RCLK = 11;    // Arduino pin connected to pin 12 (ST_CP / latch) of the 74HC595.
uint8_t SRCLK = 12;   // Arduino pin connected to pin 11 (SH_CP / clock) of the 74HC595.
uint8_t NUMOFIC = 2;  // Number of cascaded 74HC595 ICs.
uint8_t ReadPin = 2;  // Digital input pin used to select the conversion direction.

#include <DOC_CAT.h>
HC74595 Shift(NUMOFIC, SER, RCLK, SRCLK);

void setup() {
  Serial.begin(9600);
  pinMode(ReadPin, INPUT);

  Serial.println("74HC595 Number and Character to Binary Example");
  Serial.println("---------------------------------------------");
  Serial.println("Enter an integer (0-65535) or a character.");
  Serial.println("ReadPin HIGH = Number conversion");
  Serial.println("ReadPin LOW  = Character conversion");
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    if (input.length() == 0) return;

    if (digitalRead(ReadPin) == HIGH) {
      // Convert the entered integer into binary output states.
      // Syntax: NumberToBinary(int value, bool reverse);
      Shift.NumberToBinary(input.toInt(), true);
    } else {
      // Convert the first entered character into its ASCII binary representation.
      // Syntax: CharacterToBinary(char value, bool reverse);
      Shift.CharacterToBinary(input.charAt(0), true);
    }
  }
}