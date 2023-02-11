//  Produced by Dinura Pasan in February 2023 and distributed free of charge.
//  Controlling the LED Dot Matrix from within the Arduino environment.
//  Source Code --> https://github.com/DinuraPasan/DOC_CAT/

//  This sketch font data write the EEPROM spase.
//  This sketch do not touch.

#include <EEPROM.h>

const uint64_t KEY_FONT[] = {
  0x6666667e66663c00,
  0x3e66663e66663e00,
  0x3c66060606663c00,
  0x3e66666666663e00,
  0x7e06063e06067e00,
  0x0606063e06067e00,
  0x3c66760606663c00,
  0x6666667e66666600,
  0x3c18181818183c00,
  0x1c36363030307800,
  0x66361e0e1e366600,
  0x7e06060606060600,
  0xc6c6c6d6feeec600,
  0xc6c6e6f6decec600,
  0x3c66666666663c00,
  0x06063e6666663e00,
  0x603c766666663c00,
  0x66361e3e66663e00,
  0x3c66603c06663c00,
  0x18181818185a7e00,
  0x7c66666666666600,
  0x183c666666666600,
  0xc6eefed6c6c6c600,
  0xc6c66c386cc6c600,
  0x1818183c66666600,
  0x7e060c1830607e00,
  0x7c667c603c000000,
  0x3e66663e06060600,
  0x3c6606663c000000,
  0x7c66667c60606000,
  0x3c067e663c000000,
  0x0c0c0c3e0c6c3800,
  0x3c607c66667c6000,
  0x6666663e06060600,
  0x3c18181800180000,
  0x1c36363030003000,
  0x66361e3666060600,
  0x1818181818181800,
  0xd6d6feeec6000000,
  0x6666667e3e000000,
  0x3c6666663c000000,
  0x06063e66663e0000,
  0xf0b03c36363c0000,
  0x060666663e060000,
  0x3e403c027c000000,
  0x181818187e181800,
  0x7c66666666000000,
  0x183c666666000000,
  0x7cd6d6d6c6000000,
  0x663c183c66000000,
  0x3c607c6666000000,
  0x7e0c18307e000000,
  0x7ccedef6e6c67c00,
  0x7e1818181a1c1800,
  0x7e660c3860663c00,
  0x3c66603860663c00,
  0xf060fe666c787000,
  0x3c6660603e067e00,
  0x3c66663e060c3800,
  0x1818183060667e00,
  0x3c66663c66663c00,
  0x1c30607c66663c00,
  0x6030180c18306000,
  0x060c1830180c0600,
  0x6030181818306000,
  0x060c1818180c0600,
  0x7018180c18187000,
  0x0e18183018180e00,
  0x7818181818187800,
  0x1e18181818181e00,
  0x0010107c10100000,
  0x0000003c00000000,
  0x006c38fe386c0000,
  0x00060c1830600000,
  0x7e00000000000000,
  0x00007e007e000000,
  0x1800181818181800,
  0x3c421a3a221c0000,
  0x6c6cfe6cfe6c6c00,
  0x103c503814781000,
  0x60660c1830660600,
  0x000000c66c381000,
  0xbc66a61c3c663c00,
  0x0018180000181800,
  0x0c18180000181800,
  0x0018181818181800,
  0x0c18180000000000,
  0x1818000000000000,
  0x1800183866663c00,
  0x006030180c060200,
  0x00000000180c0600,
  0x000000003b6e0000,
  0x0000006666666600,
  0x0000000606060600,
  0x0000000000000000
};

const char Key[] = {
  'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
  'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
  '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '<', '>', '(', ')', '{', '}', '[', ']', '+', '-', '*', '/', '_', '=', '!', '@',
  '#', '$', '%', '^', '&', ':', ';', '|', ',', '.', '?', '\\', '`', '~', '"', '\'', ' '
};

void setup() {
  Serial.begin(9600);
  Serial.println(String(EEPROM.length()) + " byts from this ATMega Chip EEPROM Length");
  Clear();
  Key_Write();
  KEY_FONT_Write();
  Serial.println("EEPROM Write Finish");
}

void loop() {}

void Clear() {
  for (int i = 0; i < EEPROM.length(); i++) {
    EEPROM.write(i, 0);
  }
  Serial.println("EEPROM All Index Clear");
}

void Key_Write() {
  for (int i = 0; i <= 94; i++) {
    EEPROM.write(i, Key[i]);
  }
  Serial.println("EEPROM Write Key_Array Finish");
}

void KEY_FONT_Write() {
  int index = 95;
  for (int k = 0; k < 95; k++) {
    for (int i = 0; i < 8; i++) {
      byte row = (KEY_FONT[k] >> i * 8) & 0xFF;
      EEPROM.write(index, row);
      index++;
    }
  }
  Serial.println("EEPROM Write Key_Font Array Finish");
  Serial.println();
  Serial.println("Uses " + String(index - 1) + " byte for EEPROM Spase");
  Serial.println("Available " + String(EEPROM.length() - (index - 1)) + "byte EEPROM Spase");
}