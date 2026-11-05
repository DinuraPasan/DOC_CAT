//  Produced by Dinura Pasan in February 2023 and distributed free of charge.
//  Source Code --> https://github.com/DinuraPasan/DOC_CAT/

#ifndef DOC_CAT_h
#define DOC_CAT_h
#include <Arduino.h>
#include <Wire.h>
#include <EEPROM.h>

// The broadcast address of the LP503X device
#define BROADCAST 0x1C

class HC74595 {
  public:
    HC74595(uint8_t IC, uint8_t SER, uint8_t RCLK, uint8_t SRCLK);
    void Update();
    void NoUpdate(int index, bool state);
    void SetAll(bool state);
    void NumberToBinary(int value, bool reverse);
    void CharacterToBinary(char value, bool reverse);
    void SetMappedOutput(bool state, int pin, int offset[]); 
    void Sevensegment(uint8_t segments, uint8_t digitPosition, uint8_t digitCount, bool commonAnode);
    void SegmentNumber(double value, uint8_t digitPosition, uint8_t digitCount, bool commonAnode);
    void SegmentNumber(int value, uint8_t digitPosition, uint8_t digitCount, bool commonAnode);
    void LEDFlash(int duration, uint8_t pin);
    void LEDSequence(int duration, uint8_t pin);
    void LEDChase(uint8_t repetition, int duration, uint8_t startPin, uint8_t endPin, bool reverse);
    void LEDRandomFlash(uint8_t repetition, int duration, uint8_t startPin, uint8_t endPin);
    void LEDRandomToggle(uint8_t repetition, int duration, uint8_t startPin, uint8_t endPin);
    void LEDMirrorChase(uint8_t repetition, int duration, uint8_t startPin, uint8_t endPin, uint8_t divisor);
  private:
    uint8_t _IC;
    uint8_t _SER;
    uint8_t _RCLK;
    uint8_t _SRCLK;
    uint8_t *D;
    uint8_t N[20] = {
      63, 6, 91, 79, 102, 109, 125, 7, 127, 111, 191, 134, 219, 207, 230, 237, 253, 135, 255, 239
    };
};

class DotMatrix {
  public:
    DotMatrix(int X, int Y, uint8_t *A);
    void Set(int x, int y, bool type);
    void SetAll(bool type);
    void Dotset(bool type, int DD[8], byte val[]);
    void Text(char T[], bool type, int D[6]);
    void Line(int x, int y, int xx, int yy, bool type);
    void Rect(int x, int y, int width, int height, bool outline, bool colour);
    void Circle(int x, int y, int r, bool outline, bool colour);
    void Trangale(int x, int y, int xx, int yy, int xxx, int yyy, bool outline);
  private:
    int _X;
    int _Y;
    uint8_t *_A;
};

class LP503X {
  public:
    LP503X(uint8_t I2C_ADDR);
    void setColour(uint8_t LED, uint8_t value);
    uint8_t getColour(uint8_t LED);
    void setBrightness(uint8_t LED, uint8_t value);
    uint8_t getBrightness(uint8_t LED);
    void resetRegisters();
    void setRGBbank(char colour, uint8_t value, uint8_t intensity);
    void setRGBbank(uint8_t red, uint8_t green, uint8_t blue, uint8_t intensity);
    uint8_t getBankColour(char colour);
    uint8_t getBankIntensity();
    void printGrapics();
    void printBank();
    void setModule(uint8_t moduleID, bool enable);
    bool getModule(uint8_t moduleID);
    void printModule();
    void logScale(bool status);
    bool logScale();
    void Shutdown(bool status);
    bool Shutdown();
    void powerSave(bool status);
    bool powerSave();
    void autoIncrement(bool status);
    bool autoIncrement();
    void PWM_Dithering(bool status);
    bool PWM_Dithering();
    void maxCurrent(bool status);
    bool maxCurrent();
    void standby_mode();
    void normal_mode();
    void print_Settings();
  private:
    uint8_t _I2C_ADDR;
};

#endif