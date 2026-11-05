// DOC_CAT HC74595 library developed by Dinura Pasan in November 2023.
// Provides Arduino support for controlling SN74HC595 shift registers.

// Source code: https://github.com/DinuraPasan/DOC_CAT/
// SN74HC595 datasheet and product information: https://www.ti.com/product/SN74HC595

#include <DOC_CAT.h>

/// Initializes the HC74595 shift register controller.
/// @param IC Number of cascaded 74HC595 shift register ICs.
/// @param SER Serial data input pin.
/// @param RCLK Register clock (latch) pin.
/// @param SRCLK Shift register clock pin.
HC74595::HC74595(uint8_t IC, uint8_t SER, uint8_t RCLK, uint8_t SRCLK) {
  _IC = IC;
  _SER = SER;
  _RCLK = RCLK;
  _SRCLK = SRCLK;
  pinMode(SER, OUTPUT);
  pinMode(RCLK, OUTPUT);
  pinMode(SRCLK, OUTPUT);
  D = malloc(_IC);
  memset(D, 0, _IC);
}

/// Transfers stored output states to the cascaded 74HC595 shift registers and updates their physical outputs.
void HC74595::Update() {
  digitalWrite(_RCLK, LOW);
  for (int i = _IC * 8; i >= 0; i--) {
    digitalWrite(_SRCLK, LOW);
    digitalWrite(_SER, bitRead(D[i / 8], i % 8));
    digitalWrite(_SRCLK, HIGH);
  }
  digitalWrite(_RCLK, HIGH);
}

/// Changes the state of a specified output without updating the shift registers.
/// @param index Output bit index (0 to IC * 8 - 1).
/// @param state Desired output state (HIGH or LOW).
void HC74595::NoUpdate(int index, bool state) {
  bitWrite(D[index / 8], index % 8, state);
}

/// Sets all shift register outputs to the specified state and updates the registers.
/// @param state Desired state for all outputs (HIGH or LOW).
void HC74595::SetAll(bool state) {
  for (int i = 0; i < _IC * 8; i++) {
    NoUpdate(i, state);
  }
  Update();
}

/// Converts a 16-bit integer into binary output states and updates the shift registers.
/// @param value Integer value to be converted into binary.
/// @param reverse Determines the bit-mapping direction across the shift registers.
void HC74595::NumberToBinary(int value, bool reverse) {
  memset(D, 0, _IC);
  if (reverse) {
    D[0] = value;
    D[1] = value >> 8;
    Update();
  } else {
    for (byte i = 0; i < 8; i++) {
      bitWrite(D[_IC - 1], 7 - i, bitRead(value, i));
      bitWrite(D[_IC - 2], 7 - i, bitRead(value >> 8, i));
    }
    Update();
  }
}

/// Converts a character into binary output states and updates the shift registers.
/// @param value Character to be converted into binary.
/// @param reverse Determines the bit-mapping direction across the shift registers.
void HC74595::CharacterToBinary(char value, bool reverse) {
  NumberToBinary(int(value), reverse);
}

/// Displays a digit on a multiplexed seven-segment display.
/// @param segments Bit pattern representing the segments to illuminate.
/// @param digitPosition Position of the digit to activate (0-based).
/// @param digitCount Total number of multiplexed digits.
/// @param commonAnode Set true for common-anode or false for common-cathode displays.
void HC74595::Sevensegment(uint8_t segments, uint8_t digitPosition, uint8_t digitCount, bool commonAnode) {
  for (byte i = 0; i < 8; i++) {
    if (commonAnode)  NoUpdate(i, !bitRead(segments, i));
    else              NoUpdate(i, bitRead(segments, i));
  }
  for (byte i = 0; i < digitCount; i++) {
    NoUpdate(8 + i, !commonAnode);
  }
  NoUpdate(8 + digitPosition, commonAnode);
  Update();
}

/// Displays a floating-point number on a multiplexed seven-segment display, including negative signs and decimal points.
/// @param value Floating-point number to display.
/// @param digitPosition Starting digit position on the display (0-based).
/// @param digitCount Total number of multiplexed digits.
/// @param commonAnode Set true for common-anode or false for common-cathode displays.
void HC74595::SegmentNumber(double value, uint8_t digitPosition, uint8_t digitCount, bool commonAnode) {
  byte count = 0;
  String a = String(value);
  char buffer[a.length()];
  dtostrf(value, a.length(), 2, buffer);
  for (int i = 0; i < a.length(); i++) {
    if (buffer[i] == '-') {
      Sevensegment(B01000000, digitPosition, digitCount, commonAnode);
    } else if (buffer[i + 1] == '.') {
      Sevensegment(SEGMENT_PATTERNS[String(buffer[i]).toInt() + 10], digitPosition + count, digitCount, commonAnode);
      i = i + 1;
    } else {
      Sevensegment(SEGMENT_PATTERNS[String(buffer[i]).toInt()], digitPosition + count, digitCount, commonAnode);
    }
    count++;
  }
}

/// Displays an integer value on a multiplexed seven-segment display, including negative signs.
/// @param value Integer value to display.
/// @param digitPosition Starting digit position on the display (0-based).
/// @param digitCount Total number of multiplexed digits.
/// @param commonAnode Set true for common-anode or false for common-cathode displays.
void HC74595::SegmentNumber(int value, uint8_t digitPosition, uint8_t digitCount, bool commonAnode) {
  byte count = 0;
  String a = String(value);
  char buffer[a.length()];
  dtostrf(value, a.length(), 0, buffer);
  for (int i = 0; i < a.length(); i++) {
    if (buffer[i] == '-') {
      Sevensegment(B01000000, digitPosition, digitCount, commonAnode);
    } else if (buffer[i + 1] == '.') {
      Sevensegment(SEGMENT_PATTERNS[String(buffer[i]).toInt() + 10], digitPosition + count, digitCount, commonAnode);
      i = i + 1;
    } else {
      Sevensegment(SEGMENT_PATTERNS[String(buffer[i]).toInt()], digitPosition + count, digitCount, commonAnode);
    }
    count++;
  }
}

/// Flashes a specified shift register output by turning it ON and OFF.
/// @param duration Flash duration in milliseconds.
/// @param pin Shift register output pin connected to the LED.
void HC74595::LEDFlash(int duration, uint8_t pin) {
  NoUpdate(pin, HIGH);
  Update();
  delay(duration);
  NoUpdate(pin, LOW);
  Update();
}

/// Sequentially turns on and off LEDs from the specified pin down to pin 0.
/// @param duration Delay duration between LED state changes in milliseconds.
/// @param pin Highest shift register output pin in the sequence.
void HC74595::LEDSequence(int duration, uint8_t pin) {
  for (int i = pin; i > -1; i--) {
    NoUpdate(i, HIGH);
    Update();
    delay(duration);
  } for (int i = pin; i > -1; i--) {
    NoUpdate(i, LOW);
    Update();
    delay(duration);
  }
}

/// Runs a sequential LED lighting effect over a specified output range for the requested number of cycles.
/// @param repetition Number of times to repeat the LED sequence.
/// @param duration Delay duration between LED state changes in milliseconds.
/// @param startPin Starting output pin of the LED range.
/// @param endPin Ending output pin of the LED range.
/// @param reverse Determines the LED sequence direction (true = descending, false = ascending).
void HC74595::LEDChase(uint8_t repetition, int duration, uint8_t startPin, uint8_t endPin, bool reverse) {
  for (int i = 0; i < repetition; i++) {
    if (reverse) {
      for (int i = endPin; i > startPin - 1; i--) {
        NoUpdate(i, HIGH);
        Update();
        delay(duration);
      }
      for (int i = endPin; i > startPin - 1; i--) {
        NoUpdate(i, LOW);
        Update();
        delay(duration);
      }
    } else {
      for (int i = startPin; i < endPin + 1; i++) {
        NoUpdate(i, HIGH);
        Update();
        delay(duration);
      }
      for (int i = startPin; i < endPin + 1; i++) {
        NoUpdate(i, LOW);
        Update();
        delay(duration);
      }
    }
  }
}

/// Randomly flashes individual LEDs within the specified output range, turning each off before selecting the next one.
/// @param repetition Number of times to repeat the LED effect.
/// @param duration Delay duration in milliseconds.
/// @param startPin Minimum output pin index.
/// @param endPin Maximum output pin index.
void HC74595::LEDRandomFlash(uint8_t repetition, int duration, uint8_t startPin, uint8_t endPin) {
  for (int i = 0; i < repetition; i++) {
    uint8_t a = random(startPin, endPin + 1);
    NoUpdate(a, HIGH);
    Update();
    delay(duration);
    NoUpdate(a, LOW);
    Update();
    delay(duration);
  }
}

/// Randomly activates and deactivates output pins within the specified range.
/// @param repetition Number of times to repeat the LED effect.
/// @param duration Delay duration in milliseconds.
/// @param startPin Minimum output pin index.
/// @param endPin Maximum output pin index.
void HC74595::LEDRandomToggle(uint8_t repetition, int duration, uint8_t startPin, uint8_t endPin) {
  for (int i = 0; i < repetition; i++) {
    NoUpdate(random(startPin, endPin + 1), HIGH);
    Update();
    delay(duration);
    NoUpdate(random(startPin, endPin + 1), LOW);
    Update();
  }
}

/// Runs a mirrored LED lighting effect from both ends toward the center for the specified number of cycles.
/// @param repetition Number of times to repeat the LED effect.
/// @param duration Delay duration between LED state changes in milliseconds.
/// @param startPin Starting output pin index.
/// @param endPin Ending output pin index.
/// @param divisor Divisor used to determine the number of LEDs activated from each end.
void HC74595::LEDMirrorChase(uint8_t repetition, int duration, uint8_t startPin, uint8_t endPin, uint8_t divisor) {
  for (int i = 0; i < repetition; i++) {
    for (int i = startPin; i <= ((endPin - startPin) / divisor) + startPin; i++) {
      NoUpdate(i, HIGH);
      NoUpdate(endPin - (i - startPin), HIGH);
      Update();
      delay(duration);
    } for (int i = ((endPin - startPin) / divisor) + startPin; i >= startPin; i--) {
      NoUpdate(i, LOW);
      NoUpdate(endPin - (i - startPin), LOW);
      Update();
      delay(duration);
    }
  }
}