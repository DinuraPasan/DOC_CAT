//  Produced by Dinura Pasan in February 2023 and distributed free of charge.
//  Controlling the 74HC595 shift registers IC from within the Arduino environment.
//  Source Code --> https://github.com/DinuraPasan/DOC_CAT/

#include <DOC_CAT.h>

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

void HC74595::Update() {
  digitalWrite(_RCLK, LOW);
  for (int i = _IC * 8; i >= 0; i--) {
    digitalWrite(_SRCLK, LOW);
    digitalWrite(_SER, bitRead(D[i / 8], i % 8));
    digitalWrite(_SRCLK, HIGH);
  }
  digitalWrite(_RCLK, HIGH);
}

void HC74595::NoUpdate(int VV, bool V) {
  bitWrite(D[VV / 8], VV % 8, V);
}

void HC74595::SetAll(bool V) {
  for (int i = 0; i < _IC * 8; i++) {
    NoUpdate(i, V);
  }
  Update();
}

void HC74595::NumberToBinary(int valve, bool V) {
  memset(D, 0, _IC);
  if (V) {
    D[0] = valve;
    D[1] = valve >> 8;
    Update();
  } else {
    for (byte i = 0; i < 8; i++) {
      bitWrite(D[_IC - 1], 7 - i, bitRead(valve, i));
      bitWrite(D[_IC - 2], 7 - i, bitRead(valve >> 8, i));
    }
    Update();
  }
}

void HC74595::CharacterToBinary(char val, bool V) {
  NumberToBinary(int(val), V);
}

void HC74595::Location(bool valve, int pin, int Location[]) {
  int count = 0;
  for (int i = 0; i < _IC * 8; i++) {
    if (Location[i + 1] > Location[i])  count++;
    else                                break;
  }
  for (int i = 0; i <= count; i++) {
    if ((Location[i + 1] - Location[i]) > pin) {
      NoUpdate(Location[i] + pin, valve);
      Update();
    }
  }
}

void HC74595::Sevensegment(uint8_t val, uint8_t NU, uint8_t Max, bool V) {
  for (byte i = 0; i < 8; i++) {
    if (V) NoUpdate(i, !bitRead(val, i));
    else   NoUpdate(i, bitRead(val, i));
  }
  for (byte i = 0; i < Max; i++) {
    NoUpdate(8 + i, !V);
  }
  NoUpdate(8 + NU, V);
  Update();
}

void HC74595::SegmentNumber(double val, uint8_t NU, uint8_t Max, bool V) {
  byte count = 0;
  String a = String(val);
  char buffer[a.length()];
  dtostrf(val, a.length(), 2, buffer);
  for (int i = 0; i < a.length(); i++) {
    if (buffer[i] == '-') {
      Sevensegment(B01000000, NU, Max, V);
    } else if (buffer[i + 1] == '.') {
      Sevensegment(N[String(buffer[i]).toInt() + 10], NU + count, Max, V);
      i = i + 1;
    } else {
      Sevensegment(N[String(buffer[i]).toInt()], NU + count, Max, V);
    }
    count++;
  }
}

void HC74595::SegmentNumber(int val, uint8_t NU, uint8_t Max, bool V) {
  byte count = 0;
  String a = String(val);
  char buffer[a.length()];
  dtostrf(val, a.length(), 0, buffer);
  for (int i = 0; i < a.length(); i++) {
    if (buffer[i] == '-') {
      Sevensegment(B01000000, NU, Max, V);
    } else if (buffer[i + 1] == '.') {
      Sevensegment(N[String(buffer[i]).toInt() + 10], NU + count, Max, V);
      i = i + 1;
    } else {
      Sevensegment(N[String(buffer[i]).toInt()], NU + count, Max, V);
    }
    count++;
  }
}

void HC74595::LEDdesing1(int d, uint8_t pin) {
  NoUpdate(pin, HIGH);
  Update();
  delay(d);
  NoUpdate(pin, LOW);
  Update();
}

void HC74595::LEDdesing2(int d, uint8_t pin) {
  for (int i = pin; i > -1; i--) {
    NoUpdate(i, HIGH);
    Update();
    delay(d);
  } for (int i = pin; i > -1; i--) {
    NoUpdate(i, LOW);
    Update();
    delay(d);
  }
}

void HC74595::LEDdesing3(uint8_t count, int d, uint8_t Min, uint8_t Max, bool V) {
  for (int i = 0; i < count; i++) {
    if (V) {
      for (int i = Max; i > Min - 1; i--) {
        NoUpdate(i, HIGH);
        Update();
        delay(d);
      }
      for (int i = Max; i > Min - 1; i--) {
        NoUpdate(i, LOW);
        Update();
        delay(d);
      }
    } else {
      for (int i = Min; i < Max + 1; i++) {
        NoUpdate(i, HIGH);
        Update();
        delay(d);
      }
      for (int i = Min; i < Max + 1; i++) {
        NoUpdate(i, LOW);
        Update();
        delay(d);
      }
    }
  }
}

void HC74595::LEDdesing4(uint8_t count, int d, uint8_t Min, uint8_t Max) {
  for (int i = 0; i < count; i++) {
    uint8_t a = random(Min, Max + 1);
    NoUpdate(a, HIGH);
    Update();
    delay(d);
    NoUpdate(a, LOW);
    Update();
    delay(d);
  }
}

void HC74595::LEDdesing5(uint8_t count, int d, uint8_t Min, uint8_t Max) {
  for (int i = 0; i < count; i++) {
    NoUpdate(random(Min, Max + 1), HIGH);
    Update();
    delay(d);
    NoUpdate(random(Min, Max + 1), LOW);
    Update();
  }
}

void HC74595::LEDdesing6(uint8_t count, int d, uint8_t Min, uint8_t Max, uint8_t devide) {
  for (int i = 0; i < count; i++) {
    for (int i = Min; i <= ((Max - Min) / devide) + Min; i++) {
      NoUpdate(i, HIGH);
      NoUpdate(Max - (i - Min), HIGH);
      Update();
      delay(d);
    } for (int i = ((Max - Min) / devide) + Min; i >= Min; i--) {
      NoUpdate(i, LOW);
      NoUpdate(Max - (i - Min), LOW);
      Update();
      delay(d);
    }
  }
}