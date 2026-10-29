// DOC_CAT LP503X library developed by Dinura Pasan in November 2023.
// Provides Arduino support for the LP5030 and LP5036 RGB LED driver ICs.

// Source code: https://github.com/DinuraPasan/DOC_CAT/
// LP5030 datasheet and product information: https://www.ti.com/product/LP5030
// LP5036 datasheet and product information: https://www.ti.com/product/LP5036

#include <DOC_CAT.h>

// LP503X device configuration registers.
#define DEVICE_CONFIG0 0x0
#define DEVICE_CONFIG1 0x1
// LP503X RGB LED module configuration registers.
#define LED_CONFIG0 0x2
#define LED_CONFIG1 0x3
// LP503X global bank brightness register.
#define BANK_BRIGHTNESS 0x4
// LP503X RGB bank color-mixing registers.
#define BANK_A_COLOR 0x5
#define BANK_B_COLOR 0x6
#define BANK_C_COLOR 0x7
// LP503X individual RGB LED module brightness-control registers.
#define LED0_BRIGHTNESS 0x8
#define LED1_BRIGHTNESS 0x9
#define LED2_BRIGHTNESS 0xA
#define LED3_BRIGHTNESS 0xB
#define LED4_BRIGHTNESS 0xC
#define LED5_BRIGHTNESS 0xD
#define LED6_BRIGHTNESS 0xE
#define LED7_BRIGHTNESS 0xF
#define LED8_BRIGHTNESS 0x10
#define LED9_BRIGHTNESS 0x11
#define LED10_BRIGHTNESS 0x12
#define LED11_BRIGHTNESS 0x13
// LP503X individual LED output channel color-mixing registers.
#define OUT0_COLOR 0x14
#define OUT1_COLOR 0x15
#define OUT2_COLOR 0x16
#define OUT3_COLOR 0x17
#define OUT4_COLOR 0x18
#define OUT5_COLOR 0x19
#define OUT6_COLOR 0x1A
#define OUT7_COLOR 0x1B
#define OUT8_COLOR 0x1C
#define OUT9_COLOR 0x1D
#define OUT10_COLOR 0x1E
#define OUT11_COLOR 0x1F
#define OUT12_COLOR 0x20
#define OUT13_COLOR 0x21
#define OUT14_COLOR 0x22
#define OUT15_COLOR 0x23
#define OUT16_COLOR 0x24
#define OUT17_COLOR 0x25
#define OUT18_COLOR 0x26
#define OUT19_COLOR 0x27
#define OUT20_COLOR 0x28
#define OUT21_COLOR 0x29
#define OUT22_COLOR 0x2A
#define OUT23_COLOR 0x2B
#define OUT24_COLOR 0x2C
#define OUT25_COLOR 0x2D
#define OUT26_COLOR 0x2E
#define OUT27_COLOR 0x2F
#define OUT28_COLOR 0x30
#define OUT29_COLOR 0x31
#define OUT30_COLOR 0x32
#define OUT31_COLOR 0x33
#define OUT32_COLOR 0x34
#define OUT33_COLOR 0x35
#define OUT34_COLOR 0x36
#define OUT35_COLOR 0x37
// LP503X software reset register.
#define RESET 0x38
// LP503X RGB LED module selectors for RGB bank control mode (modules 0–11).
#define LED0_Bank_EN 0
#define LED1_Bank_EN 1
#define LED2_Bank_EN 2
#define LED3_Bank_EN 3
#define LED4_Bank_EN 4
#define LED5_Bank_EN 5
#define LED6_Bank_EN 6
#define LED7_Bank_EN 7
#define LED8_Bank_EN 8
#define LED9_Bank_EN 9
#define LED10_Bank_EN 10
#define LED11_Bank_EN 11

/// Initializes the LP503X driver with the specified I2C address.
/// @param I2C_ADDR I2C address of the LP503X device.
LP503X::LP503X(uint8_t I2C_ADDR) {
  _I2C_ADDR = I2C_ADDR;
   Wire.begin();
}

/// Sets the color-mixing level of an individual LED output channel.
/// @param LED   LED output index (0–29 for LP5030, 0–35 for LP5036).
/// @param value Color-mixing level (0–255).
void LP503X::setColour(uint8_t LED, uint8_t value) {
  if ((LED >= 0) && (LED <= 35)) {
    Wire.beginTransmission(_I2C_ADDR);
    if (LED == 0) Wire.write(OUT0_COLOR);
    else if (LED == 1) Wire.write(OUT1_COLOR);
    else if (LED == 2) Wire.write(OUT2_COLOR);
    else if (LED == 3) Wire.write(OUT3_COLOR);
    else if (LED == 4) Wire.write(OUT4_COLOR);
    else if (LED == 5) Wire.write(OUT5_COLOR);
    else if (LED == 6) Wire.write(OUT6_COLOR);
    else if (LED == 7) Wire.write(OUT7_COLOR);
    else if (LED == 8) Wire.write(OUT8_COLOR);
    else if (LED == 9) Wire.write(OUT9_COLOR);
    else if (LED == 10) Wire.write(OUT10_COLOR);
    else if (LED == 11) Wire.write(OUT11_COLOR);
    else if (LED == 12) Wire.write(OUT12_COLOR);
    else if (LED == 13) Wire.write(OUT13_COLOR);
    else if (LED == 14) Wire.write(OUT14_COLOR);
    else if (LED == 15) Wire.write(OUT15_COLOR);
    else if (LED == 16) Wire.write(OUT16_COLOR);
    else if (LED == 17) Wire.write(OUT17_COLOR);
    else if (LED == 18) Wire.write(OUT18_COLOR);
    else if (LED == 19) Wire.write(OUT19_COLOR);
    else if (LED == 20) Wire.write(OUT20_COLOR);
    else if (LED == 21) Wire.write(OUT21_COLOR);
    else if (LED == 22) Wire.write(OUT22_COLOR);
    else if (LED == 23) Wire.write(OUT23_COLOR);
    else if (LED == 24) Wire.write(OUT24_COLOR);
    else if (LED == 25) Wire.write(OUT25_COLOR);
    else if (LED == 26) Wire.write(OUT26_COLOR);
    else if (LED == 27) Wire.write(OUT27_COLOR);
    else if (LED == 28) Wire.write(OUT28_COLOR);
    else if (LED == 29) Wire.write(OUT29_COLOR);
    else if (LED == 30) Wire.write(OUT30_COLOR);
    else if (LED == 31) Wire.write(OUT31_COLOR);
    else if (LED == 32) Wire.write(OUT32_COLOR);
    else if (LED == 33) Wire.write(OUT33_COLOR);
    else if (LED == 34) Wire.write(OUT34_COLOR);
    else if (LED == 35) Wire.write(OUT35_COLOR);
    Wire.write(value);
    Wire.endTransmission();
  }
}

/// Gets the color-mixing level of an individual LED output channel.
/// @param LED LED output index (0–29 for LP5030, 0–35 for LP5036).
/// @return Color-mixing level (0–255).
uint8_t LP503X::getColour(uint8_t LED) {
  if ((LED >= 0) && (LED <= 35)) {
    Wire.beginTransmission(_I2C_ADDR);
    if (LED == 0) Wire.write(OUT0_COLOR);
    else if (LED == 1) Wire.write(OUT1_COLOR);
    else if (LED == 2) Wire.write(OUT2_COLOR);
    else if (LED == 3) Wire.write(OUT3_COLOR);
    else if (LED == 4) Wire.write(OUT4_COLOR);
    else if (LED == 5) Wire.write(OUT5_COLOR);
    else if (LED == 6) Wire.write(OUT6_COLOR);
    else if (LED == 7) Wire.write(OUT7_COLOR);
    else if (LED == 8) Wire.write(OUT8_COLOR);
    else if (LED == 9) Wire.write(OUT9_COLOR);
    else if (LED == 10) Wire.write(OUT10_COLOR);
    else if (LED == 11) Wire.write(OUT11_COLOR);
    else if (LED == 12) Wire.write(OUT12_COLOR);
    else if (LED == 13) Wire.write(OUT13_COLOR);
    else if (LED == 14) Wire.write(OUT14_COLOR);
    else if (LED == 15) Wire.write(OUT15_COLOR);
    else if (LED == 16) Wire.write(OUT16_COLOR);
    else if (LED == 17) Wire.write(OUT17_COLOR);
    else if (LED == 18) Wire.write(OUT18_COLOR);
    else if (LED == 19) Wire.write(OUT19_COLOR);
    else if (LED == 20) Wire.write(OUT20_COLOR);
    else if (LED == 21) Wire.write(OUT21_COLOR);
    else if (LED == 22) Wire.write(OUT22_COLOR);
    else if (LED == 23) Wire.write(OUT23_COLOR);
    else if (LED == 24) Wire.write(OUT24_COLOR);
    else if (LED == 25) Wire.write(OUT25_COLOR);
    else if (LED == 26) Wire.write(OUT26_COLOR);
    else if (LED == 27) Wire.write(OUT27_COLOR);
    else if (LED == 28) Wire.write(OUT28_COLOR);
    else if (LED == 29) Wire.write(OUT29_COLOR);
    else if (LED == 30) Wire.write(OUT30_COLOR);
    else if (LED == 31) Wire.write(OUT31_COLOR);
    else if (LED == 32) Wire.write(OUT32_COLOR);
    else if (LED == 33) Wire.write(OUT33_COLOR);
    else if (LED == 34) Wire.write(OUT34_COLOR);
    else if (LED == 35) Wire.write(OUT35_COLOR);
    Wire.endTransmission(false);
    Wire.requestFrom(int(_I2C_ADDR), 1);
    return Wire.read();
  }
}

/// Sets the brightness level of an individual RGB LED output channel.
/// @param LED   LED output index (0–29 for LP5030, 0–35 for LP5036).
/// @param value Brightness level (0–255).
void LP503X::setBrightness(uint8_t LED, uint8_t value) {
  if ((LED >= 0) && (LED <= 35)) {
    Wire.beginTransmission(_I2C_ADDR);
    if (LED == 0 || LED == 1 || LED == 2) Wire.write(LED0_BRIGHTNESS);
    else if (LED == 3 || LED == 4 || LED == 5) Wire.write(LED1_BRIGHTNESS);
    else if (LED == 6 || LED == 7 || LED == 8) Wire.write(LED2_BRIGHTNESS);
    else if (LED == 9 || LED == 10 || LED == 11) Wire.write(LED3_BRIGHTNESS);
    else if (LED == 12 || LED == 13 || LED == 14) Wire.write(LED4_BRIGHTNESS);
    else if (LED == 15 || LED == 16 || LED == 17) Wire.write(LED5_BRIGHTNESS);
    else if (LED == 18 || LED == 19 || LED == 20) Wire.write(LED6_BRIGHTNESS);
    else if (LED == 21 || LED == 22 || LED == 23) Wire.write(LED7_BRIGHTNESS);
    else if (LED == 24 || LED == 25 || LED == 26) Wire.write(LED8_BRIGHTNESS);
    else if (LED == 27 || LED == 28 || LED == 29) Wire.write(LED9_BRIGHTNESS);
    else if (LED == 30 || LED == 31 || LED == 32) Wire.write(LED10_BRIGHTNESS);
    else if (LED == 33 || LED == 34 || LED == 35) Wire.write(LED11_BRIGHTNESS);
    Wire.write(value);
    Wire.endTransmission();
  }
}

/// Gets the brightness level of an individual LED output channel.
/// @param LED LED output index (0–29 for LP5030, 0–35 for LP5036).
/// @return Brightness level (0–255).
uint8_t LP503X::getBrightness(uint8_t LED) {
  if ((LED >= 0) && (LED <= 35)) {
    Wire.beginTransmission(_I2C_ADDR);
    if (LED == 0 || LED == 1 || LED == 2) Wire.write(LED0_BRIGHTNESS);
    else if (LED == 3 || LED == 4 || LED == 5) Wire.write(LED1_BRIGHTNESS);
    else if (LED == 6 || LED == 7 || LED == 8) Wire.write(LED2_BRIGHTNESS);
    else if (LED == 9 || LED == 10 || LED == 11) Wire.write(LED3_BRIGHTNESS);
    else if (LED == 12 || LED == 13 || LED == 14) Wire.write(LED4_BRIGHTNESS);
    else if (LED == 15 || LED == 16 || LED == 17) Wire.write(LED5_BRIGHTNESS);
    else if (LED == 18 || LED == 19 || LED == 20) Wire.write(LED6_BRIGHTNESS);
    else if (LED == 21 || LED == 22 || LED == 23) Wire.write(LED7_BRIGHTNESS);
    else if (LED == 24 || LED == 25 || LED == 26) Wire.write(LED8_BRIGHTNESS);
    else if (LED == 27 || LED == 28 || LED == 29) Wire.write(LED9_BRIGHTNESS);
    else if (LED == 30 || LED == 31 || LED == 32) Wire.write(LED10_BRIGHTNESS);
    else if (LED == 33 || LED == 34 || LED == 35) Wire.write(LED11_BRIGHTNESS);
    Wire.endTransmission(false);
    Wire.requestFrom(int(_I2C_ADDR), 1);
    return Wire.read();
  }
}

/// Resets all internal registers to their default values.
void LP503X::resetRegisters() {
  Wire.beginTransmission(_I2C_ADDR);
  Wire.write(RESET);
  Wire.write(0xFF);
  Wire.endTransmission();
}

/// Sets the color-mixing level and global brightness of an RGB color bank.
/// @param colour Color bank selector ('R'/'r' for red, 'G'/'g' for green, 'B'/'b' for blue).
/// @param value Color-mixing level (0–255).
/// @param intensity Global brightness level for enabled LED banks (0–255).
void LP503X::setRGBbank(char colour, uint8_t value, uint8_t intensity) {
  if (colour == 'R' || colour == 'r' || colour == 'G' || colour == 'g' || colour == 'B' || colour == 'b') {
    Wire.beginTransmission(_I2C_ADDR);
    if (colour == 'R' || colour == 'r') {
      Wire.write(BANK_A_COLOR);
    } else if (colour == 'G' || colour == 'g') {
      Wire.write(BANK_B_COLOR);
    } else if (colour == 'B' || colour == 'b') {
      Wire.write(BANK_C_COLOR);
    }
    Wire.write(value);
    Wire.endTransmission(false);
    Wire.beginTransmission(_I2C_ADDR);
    Wire.write(BANK_BRIGHTNESS);
    Wire.write(intensity);
    Wire.endTransmission();
  }
}

/// Sets the color-mixing levels of all RGB color banks simultaneously.
/// @param red       Red bank color-mixing level (0–255).
/// @param green     Green bank color-mixing level (0–255).
/// @param blue      Blue bank color-mixing level (0–255).
/// @param intensity Global brightness level for enabled LED banks (0–255).
void LP503X::setRGBbank(uint8_t red, uint8_t green, uint8_t blue, uint8_t intensity) {
  Wire.beginTransmission(_I2C_ADDR);
  Wire.write(BANK_A_COLOR);
  Wire.write(red);
  Wire.endTransmission(false);
  Wire.beginTransmission(_I2C_ADDR);
  Wire.write(BANK_B_COLOR);
  Wire.write(green);
  Wire.endTransmission(false);
  Wire.beginTransmission(_I2C_ADDR);
  Wire.write(BANK_C_COLOR);
  Wire.write(blue);
  Wire.endTransmission(false);
  Wire.beginTransmission(_I2C_ADDR);
  Wire.write(BANK_BRIGHTNESS);
  Wire.write(intensity);
  Wire.endTransmission();
}

/// Gets the color-mixing level of the specified RGB color bank.
/// @param colour Color bank selector ('R'/'r' for red, 'G'/'g' for green, 'B'/'b' for blue).
/// @return Color-mixing level (0–255).
uint8_t LP503X::getBankColour(char colour) {
  if (colour == 'R' || colour == 'r' || colour == 'G' || colour == 'g' || colour == 'B' || colour == 'b') {
    Wire.beginTransmission(_I2C_ADDR);
    if (colour == 'R' || colour == 'r') {
      Wire.write(BANK_A_COLOR);
    } else if (colour == 'G' || colour == 'g') {
      Wire.write(BANK_B_COLOR);
    } else if (colour == 'B' || colour == 'b') {
      Wire.write(BANK_C_COLOR);
    }
    Wire.endTransmission(false);
    Wire.requestFrom(int(_I2C_ADDR), 1);
    return Wire.read();
  }
}

/// Gets the global brightness level of all enabled LED banks.
/// @return Bank brightness level (0–255).
uint8_t LP503X::getBankIntensity() {
  Wire.beginTransmission(_I2C_ADDR);
  Wire.write(BANK_BRIGHTNESS);
  Wire.endTransmission(false);
  Wire.requestFrom(int(_I2C_ADDR), 1);
  return Wire.read();
}

/// Prints the color-mixing and brightness levels of all LED output channels to the Serial Monitor.
void LP503X::printGrapics() {
  for (byte i = 0; i <= 35; i++) {
    Serial.println("Index : " + String(i) + "\tColor-Mixing level : " + String(getColour(i)) + "\tIntensity level : " + String(getBrightness(i)));
  }
}

/// Prints the color-mixing levels of all RGB banks and their global brightness level to the Serial Monitor.
void LP503X::printBank() {
  Serial.println("Red bank color mixing level : " + String(getBankColour('R')));
  Serial.println("Green bank color mixing level : " + String(getBankColour('G')));
  Serial.println("Blue bank color mixing level : " + String(getBankColour('B')));
  Serial.println("Bank intensity level : " + String(getBankIntensity()));
}

/// Enables or disables an LED module for RGB bank control.
/// @param moduleID LED module selector (LED0_Bank_EN to LED11_Bank_EN, corresponding to modules 0–11).
/// @param enable   Set to true to enable or false to disable bank control for the selected module.
void LP503X::setModule(uint8_t moduleID, bool enable) {
  if (moduleID >= 0 && moduleID <= 7) {
    Wire.beginTransmission(_I2C_ADDR);
    Wire.write(LED_CONFIG0);
    Wire.endTransmission(false);
    Wire.requestFrom(int(_I2C_ADDR), 1, false);
    byte tag = Wire.read();
    bitWrite(tag, moduleID, enable);
    Wire.beginTransmission(_I2C_ADDR);
    Wire.write(LED_CONFIG0);
    Wire.write(tag);
    Wire.endTransmission();
  } else if (moduleID >= 8 && moduleID <= 11) {
    Wire.beginTransmission(_I2C_ADDR);
    Wire.write(LED_CONFIG1);
    Wire.endTransmission(false);
    Wire.requestFrom(int(_I2C_ADDR), 1, false);
    byte tag = Wire.read();
    bitWrite(tag, moduleID - 8, enable);
    Wire.beginTransmission(_I2C_ADDR);
    Wire.write(LED_CONFIG1);
    Wire.write(tag);
    Wire.endTransmission();
  }
}

/// Checks whether an LED module is enabled for RGB bank control.
/// @param moduleID LED module selector (LED0_Bank_EN to LED11_Bank_EN, corresponding to modules 0–11).
/// @return true if bank control is enabled; otherwise, false.
bool LP503X::getModule(uint8_t moduleID) {
  if (moduleID >= 0 && moduleID <= 7) {
    Wire.beginTransmission(_I2C_ADDR);
    Wire.write(LED_CONFIG0);
    Wire.endTransmission(false);
    Wire.requestFrom(int(_I2C_ADDR), 1);
    byte tag = Wire.read();
    return bitRead(tag, moduleID);
  } else if (moduleID >= 8 && moduleID <= 11) {
    Wire.beginTransmission(_I2C_ADDR);
    Wire.write(LED_CONFIG1);
    Wire.endTransmission(false);
    Wire.requestFrom(int(_I2C_ADDR), 1);
    byte tag = Wire.read();
    return bitRead(tag, moduleID - 8);
  }
}

/// Prints the enable/disable status of all 12 LED modules to the Serial Monitor.
void LP503X::printModule() {
  String text = "";
  for (byte i = 0; i < 12; i++) {
    text = (getModule(i) == true) ? "Enable" : "Disable";
    Serial.println("BankID : " + String(i) + "\tState : " + text);
  }
}

/// Configures the LED dimming curve.
/// @param status Set to true for logarithmic dimming or false for linear dimming.
void LP503X::logScale(bool status) {
  Wire.beginTransmission(_I2C_ADDR);
  Wire.write(DEVICE_CONFIG1);
  Wire.endTransmission(false);
  Wire.requestFrom(int(_I2C_ADDR), 1, false);
  byte tag = Wire.read();
  bitWrite(tag, 5, status);
  Wire.beginTransmission(_I2C_ADDR);
  Wire.write(DEVICE_CONFIG1);
  Wire.write(tag);
  Wire.endTransmission();
}

/// Gets the currently configured LED dimming curve.
/// @return true for logarithmic dimming; false for linear dimming.
bool LP503X::logScale() {
  Wire.beginTransmission(_I2C_ADDR);
  Wire.write(DEVICE_CONFIG1);
  Wire.endTransmission(false);
  Wire.requestFrom(int(_I2C_ADDR), 1);
  byte tag = Wire.read();
  return bitRead(tag, 5);
}

/// Enables or disables the global shutdown mode for all LEDs.
/// @param status Set to true to shut down all LEDs or false for normal operation.
void LP503X::Shutdown(bool status) {
  Wire.beginTransmission(_I2C_ADDR);
  Wire.write(DEVICE_CONFIG1);
  Wire.endTransmission(false);
  Wire.requestFrom(int(_I2C_ADDR), 1, false);
  byte tag = Wire.read();
  bitWrite(tag, 0, status);
  Wire.beginTransmission(_I2C_ADDR);
  Wire.write(DEVICE_CONFIG1);
  Wire.write(tag);
  Wire.endTransmission();
}

/// Checks whether the global LED shutdown mode is enabled.
/// @return true if shutdown is enabled; otherwise, false.
bool LP503X::Shutdown() {
  Wire.beginTransmission(_I2C_ADDR);
  Wire.write(DEVICE_CONFIG1);
  Wire.endTransmission(false);
  Wire.requestFrom(int(_I2C_ADDR), 1);
  byte tag = Wire.read();
  return bitRead(tag, 0);
}

/// Enables or disables automatic power-saving mode.
/// @param status Set to true to enable or false to disable power-saving mode.
void LP503X::powerSave(bool status) {
  Wire.beginTransmission(_I2C_ADDR);
  Wire.write(DEVICE_CONFIG1);
  Wire.endTransmission(false);
  Wire.requestFrom(int(_I2C_ADDR), 1, false);
  byte tag = Wire.read();
  bitWrite(tag, 4, status);
  Wire.beginTransmission(_I2C_ADDR);
  Wire.write(DEVICE_CONFIG1);
  Wire.write(tag);
  Wire.endTransmission();
}

/// Checks whether automatic power-saving mode is enabled.
/// @return true if enabled; otherwise, false.
bool LP503X::powerSave() {
  Wire.beginTransmission(_I2C_ADDR);
  Wire.write(DEVICE_CONFIG1);
  Wire.endTransmission(false);
  Wire.requestFrom(int(_I2C_ADDR), 1);
  byte tag = Wire.read();
  return bitRead(tag, 4);
}

/// Enables or disables the register auto-increment feature.
/// @param status Set to true to enable or false to disable auto-increment mode.
void LP503X::autoIncrement(bool status) {
  Wire.beginTransmission(_I2C_ADDR);
  Wire.write(DEVICE_CONFIG1);
  Wire.endTransmission(false);
  Wire.requestFrom(int(_I2C_ADDR), 1, false);
  byte tag = Wire.read();
  bitWrite(tag, 3, status);
  Wire.beginTransmission(_I2C_ADDR);
  Wire.write(DEVICE_CONFIG1);
  Wire.write(tag);
  Wire.endTransmission();
}

/// Checks whether register auto-increment mode is enabled.
/// @return true if enabled; otherwise, false.
bool LP503X::autoIncrement() {
  Wire.beginTransmission(_I2C_ADDR);
  Wire.write(DEVICE_CONFIG1);
  Wire.endTransmission(false);
  Wire.requestFrom(int(_I2C_ADDR), 1);
  byte tag = Wire.read();
  return bitRead(tag, 3);
}

/// Enables or disables PWM dithering.
/// @param status Set to true to enable or false to disable PWM dithering.
void LP503X::PWM_Dithering(bool status) {
  Wire.beginTransmission(_I2C_ADDR);
  Wire.write(DEVICE_CONFIG1);
  Wire.endTransmission(false);
  Wire.requestFrom(int(_I2C_ADDR), 1, false);
  byte tag = Wire.read();
  bitWrite(tag, 2, status);
  Wire.beginTransmission(_I2C_ADDR);
  Wire.write(DEVICE_CONFIG1);
  Wire.write(tag);
  Wire.endTransmission();
}

/// Checks whether PWM dithering is enabled.
/// @return true if enabled; otherwise, false.
bool LP503X::PWM_Dithering() {
  Wire.beginTransmission(_I2C_ADDR);
  Wire.write(DEVICE_CONFIG1);
  Wire.endTransmission(false);
  Wire.requestFrom(int(_I2C_ADDR), 1);
  byte tag = Wire.read();
  return bitRead(tag, 2);
}

/// Configures the maximum output current limit.
/// @param status Set to true for 35 mA or false for 25.5 mA.
void LP503X::maxCurrent(bool status) {
  Wire.beginTransmission(_I2C_ADDR);
  Wire.write(DEVICE_CONFIG1);
  Wire.endTransmission(false);
  Wire.requestFrom(int(_I2C_ADDR), 1, false);
  byte tag = Wire.read();
  bitWrite(tag, 1, status);
  Wire.beginTransmission(_I2C_ADDR);
  Wire.write(DEVICE_CONFIG1);
  Wire.write(tag);
  Wire.endTransmission();
}

/// Gets the configured maximum output current limit.
/// @return true for 35 mA; false for 25.5 mA.
bool LP503X::maxCurrent() {
  Wire.beginTransmission(_I2C_ADDR);
  Wire.write(DEVICE_CONFIG1);
  Wire.endTransmission(false);
  Wire.requestFrom(int(_I2C_ADDR), 1);
  byte tag = Wire.read();
  return bitRead(tag, 1);
}

/// Places the LP503X device in standby mode.
void LP503X::standby_mode() {
  Wire.beginTransmission(_I2C_ADDR);
  Wire.write(DEVICE_CONFIG0);
  Wire.endTransmission(false);
  Wire.requestFrom(int(_I2C_ADDR), 1, false);
  byte tag = Wire.read();
  bitWrite(tag, 6, false);
  Wire.beginTransmission(_I2C_ADDR);
  Wire.write(DEVICE_CONFIG0);
  Wire.write(tag);
  Wire.endTransmission();
}

/// Places the LP503X device in normal operating mode.
void LP503X::normal_mode() {
  Wire.beginTransmission(_I2C_ADDR);
  Wire.write(DEVICE_CONFIG0);
  Wire.endTransmission(false);
  Wire.requestFrom(int(_I2C_ADDR), 1, false);
  byte tag = Wire.read();
  bitWrite(tag, 6, true);
  Wire.beginTransmission(_I2C_ADDR);
  Wire.write(DEVICE_CONFIG0);
  Wire.write(tag);
  Wire.endTransmission();
}

/// Prints the current configuration settings of the LP503X device to the Serial Monitor.
void LP503X::print_Settings() {
  Wire.beginTransmission(_I2C_ADDR);
  Wire.write(DEVICE_CONFIG1);
  Wire.endTransmission(false);
  Wire.requestFrom(int(_I2C_ADDR), 1);
  byte tag = Wire.read();
  (bitRead(tag, 0)) ? Serial.println("All LEDs are disabled.") : Serial.println("The LP503X device works in normal operation.");
  (bitRead(tag, 1)) ? Serial.println("The maximum current limit of the LP503X device is set to 35mA.") : Serial.println("The maximum current limit of the LP503X device is set to 25.5mA.");
  (bitRead(tag, 2)) ? Serial.println("PWM dithering mode enabled.") : Serial.println("PWM dithering mode disabled.");
  (bitRead(tag, 3)) ? Serial.println("Automatic increment mode enabled.") : Serial.println("Automatic increment mode disabled.");
  (bitRead(tag, 4)) ? Serial.println("Automatic power-saving mode enabled.") : Serial.println("Automatic power-saving mode disabled.");
  (bitRead(tag, 5)) ? Serial.println("Logarithmic scale dimming curve enabled.") : Serial.println("Linear scale dimming curve enabled.");
}