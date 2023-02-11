//  Produced by Dinura Pasan in February 2023 and distributed free of charge.
//  Source Code --> https://github.com/DinuraPasan/DOC_CAT/

#ifndef DOC_CAT_h
#define DOC_CAT_h
#include <Arduino.h>
#include <Wire.h>
#include <EEPROM.h>

class DS3231 {
  public:
    DS3231(uint8_t V);
    uint8_t GetAgingOffset();
    uint8_t Second();
    uint8_t Minute();
    uint8_t Hour();
    uint8_t Day();
    uint8_t Date();
    uint8_t Month();
    float Converter(uint8_t V, float val);
    float Temperature();
    String Weekday(int y, uint8_t m, uint8_t d);
    String NameOfMonth();
    String NameOfDay();
    void TimeCal(uint8_t H0, uint8_t M0, uint8_t S0, uint8_t H1, uint8_t M1, uint8_t S1, uint8_t out[3], bool V);
    void DateCal(int Y0, uint8_t M0, uint8_t D0, int Y1, uint8_t M1, uint8_t D1, int out[3], bool V);
    void Return_Alarm(uint8_t month, uint8_t VV, uint8_t HH, uint8_t MM, uint8_t SS, uint8_t RT[5]);
    void Set(int YY, uint8_t MM, uint8_t DD, uint8_t HH, uint8_t mm, uint8_t SS, uint8_t WEAK);
    void Alarm_Write(uint8_t VV, uint8_t HH, uint8_t MM, uint8_t SS, bool Alarm);
    void Next_Alarm(bool V, uint8_t AT[4], uint8_t RT[4]);
    void SQW_Pin(bool BS, uint8_t SQ);
    void Alarm_Interrupt(uint8_t SQ);
    void SetAgingOffset(uint8_t V);
    void Oscillator(bool V);
    void EN32K_Pin(bool V);
    bool Alarm_State(bool V);
    bool Oscillator_State();
    int Year();
  private:
    int _Year;
    bool Year100 = false;
    uint8_t BTD(uint8_t V);
    uint8_t DTB(uint8_t V);
};

class HC74595 {
  public:
    HC74595(uint8_t IC, uint8_t SER, uint8_t RCLK, uint8_t SRCLK);
    void Update();
    void NoUpdate(int index, bool V);
    void SetAll(bool V);
    void NumberToBinary(int valve, bool V);
    void CharacterToBinary(char val, bool V);
    void Location(bool valve, int pin, int Location[]);
    void Sevensegment(uint8_t val, uint8_t NU, uint8_t Max, bool V);
    void SegmentNumber(double val, uint8_t NU, uint8_t Max, bool V);
    void SegmentNumber(int val, uint8_t NU, uint8_t Max, bool V);
    void LEDdesing1(int d, uint8_t pin);
    void LEDdesing2(int d, uint8_t pin);
    void LEDdesing3(uint8_t count, int d, uint8_t Min, uint8_t Max, bool V);
    void LEDdesing4(uint8_t count, int d, uint8_t Min, uint8_t Max);
    void LEDdesing5(uint8_t count, int d, uint8_t Min, uint8_t Max);
    void LEDdesing6(uint8_t count, int d, uint8_t Min, uint8_t Max, uint8_t devide);
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
#endif