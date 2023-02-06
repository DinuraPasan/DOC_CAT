//  Produced by Dinura Pasan in February 2023 and distributed free of charge.
//  Controlling the DS3231 RTC IC from within the Arduino environment.
//  Source Code --> https://github.com/DinuraPasan/DOC_CAT/

#include <DOC_CAT.h>

DS3231::DS3231(uint8_t V) {
  Wire.begin();
  _Year = (abs(V) - 1) * 100;
}

uint8_t DS3231::GetAgingOffset() {
  Wire.beginTransmission(0x68);
  Wire.write(0x10);
  Wire.endTransmission(false);
  Wire.requestFrom(0x68, 1);
  uint8_t V = Wire.read();
  if (V > 127)  V =  V - 256;
  return V;
}

uint8_t DS3231::Second() {
  Wire.beginTransmission(0x68);
  Wire.write(0x0);
  Wire.endTransmission(false);
  Wire.requestFrom(0x68, 1);
  return BTD(Wire.read());
}

uint8_t DS3231::Minute() {
  Wire.beginTransmission(0x68);
  Wire.write(0x1);
  Wire.endTransmission(false);
  Wire.requestFrom(0x68, 1);
  return BTD(Wire.read());
}

uint8_t DS3231::Hour() {
  Wire.beginTransmission(0x68);
  Wire.write(0x2);
  Wire.endTransmission(false);
  Wire.requestFrom(0x68, 1);
  return BTD(Wire.read());
}

uint8_t DS3231::Day() {
  Wire.beginTransmission(0x68);
  Wire.write(0x3);
  Wire.endTransmission(false);
  Wire.requestFrom(0x68, 1);
  return BTD(Wire.read());
}

uint8_t DS3231::Date() {
  Wire.beginTransmission(0x68);
  Wire.write(0x4);
  Wire.endTransmission(false);
  Wire.requestFrom(0x68, 1);
  return BTD(Wire.read());
}

uint8_t DS3231::Month() {
  Wire.beginTransmission(0x68);
  Wire.write(0x5);
  Wire.endTransmission(false);
  Wire.requestFrom(0x68, 1);
  uint8_t V = Wire.read();
  V = bitWrite(V, 7, 0);
  return ((V / 16 * 10) + (V % 16));
}

uint8_t DS3231::BTD(uint8_t V) {
  return ((V / 16 * 10) + (V % 16));
}

uint8_t DS3231::DTB(uint8_t V) {
  return ((V / 10 * 16) + (V % 10));
}

float DS3231::Converter(uint8_t V, float val) {
  if (V == 0)       return val * 0.0166666667;   //sec > min
  else if (V == 1)  return val * 0.0002777778;   //sec >hour
  else if (V == 2)  return val * 0.0000115741;   //sec >day
  else if (V == 3)  return val * 0.0000016534;   //sec >weeks
  else if (V == 4)  return val * 3.80265176e-7;  //sec >month
  else if (V == 5)  return val * 3.16887646e-8;  //sec >year
  else if (V == 6)  return val * 60.0;           //min >sec
  else if (V == 7)  return val * 0.0166666667;   //min >hour
  else if (V == 8)  return val * 0.00069444445;  //min >day
  else if (V == 9)  return val * 0.00009920634;  //min >weeks
  else if (V == 10) return val * 0.00002281591;  //min >month
  else if (V == 11) return val * 0.00000190132;  //min >year
  else if (V == 12) return val * 3600.0;         //hour >sec
  else if (V == 13) return val * 60.0;           //hour >min
  else if (V == 14) return val * 0.0416666667;   //hour >day
  else if (V == 15) return val * 0.00595238095;  //hour >weeks
  else if (V == 16) return val * 0.00136895463;  //hour >month
  else if (V == 17) return val * 0.00011407955;  //hour >year
  else if (V == 18) return val * 86400.0;        //day >sec
  else if (V == 19) return val * 1440.0;         //day >min
  else if (V == 20) return val * 24.0;           //day >hour
  else if (V == 21) return val * 0.142857143;    //day >weeks
  else if (V == 22) return val * 0.0328549112;   //day >month
  else if (V == 23) return val * 0.00273790926;  //day >year
  else if (V == 24) return val * 604800.0;       //weeks >sec
  else if (V == 25) return val * 10080.0;        //weeks >min
  else if (V == 26) return val * 168.0;          //weeks >hour
  else if (V == 27) return val * 7.0;            //weeks >day
  else if (V == 28) return val * 0.229984378;    //weeks >month
  else if (V == 29) return val * 0.0191653649;   //weeks >year
  else if (V == 30) return val * 2629743.83;     //month >sec
  else if (V == 31) return val * 43829.0639;     //month >min
  else if (V == 32) return val * 730.484398;     //month >hour
  else if (V == 33) return val * 30.4368499;     //month >day
  else if (V == 34) return val * 4.34812141;     //month >weeks
  else if (V == 35) return val * 0.0833333333;   //month >year
  else if (V == 36) return val * 31556926.0;     //year >sec
  else if (V == 37) return val * 525948.766;     //year >min
  else if (V == 38) return val * 8765.81277;     //year >hour
  else if (V == 39) return val * 365.242199;     //year >day
  else if (V == 40) return val * 52.177457;      //year >weeks
  else if (V == 41) return val * 12.0;           //year >month
  else              return val;
}

float DS3231::Temperature() {
  Wire.beginTransmission(0x68);
  Wire.write(0x11);
  Wire.endTransmission(false);
  Wire.requestFrom(0x68, 2);
  return ((Wire.read() << 8 | Wire.read()) >> 6) / 4.0;
}

String DS3231::Weekday(int y, uint8_t m, uint8_t d) {
  int LeapYears = y / 4;
  long a = (y - LeapYears) * 365 + LeapYears * 366;
  if (m >= 2) a += 31;
  if (m >= 3 && (int)y / 4 == y / 4) a += 29;
  else if (m >= 3) a += 28;
  if (m >= 4)   a += 31;
  if (m >= 5)   a += 30;
  if (m >= 6)   a += 31;
  if (m >= 7)   a += 30;
  if (m >= 8)   a += 31;
  if (m >= 9)   a += 31;
  if (m >= 10)  a += 30;
  if (m >= 11)  a += 31;
  if (m == 12)  a += 30;
  a += d;
  if (((a - 2)  % 7) == 1)    return "Monday";
  if (((a - 2)  % 7) == 2)    return "Tuesday";
  if (((a - 2)  % 7) == 3)    return "Wednesday";
  if (((a - 2)  % 7) == 4)    return "Thursday";
  if (((a - 2)  % 7) == 5)    return "Friday";
  if (((a - 2)  % 7) == 6)    return "Saturday";
  if (((a - 2)  % 7) == 7)    return "Sunday";
}

String DS3231::NameOfMonth() {
  uint8_t V = Month();
  if (V == 1)        return "January";
  else if (V == 2)   return "February";
  else if (V == 3)   return "March";
  else if (V == 4)   return "April";
  else if (V == 5)   return "May";
  else if (V == 6)   return "Jun";
  else if (V == 7)   return "July";
  else if (V == 8)   return "August";
  else if (V == 9)   return "September";
  else if (V == 10)  return "October";
  else if (V == 11)  return "November";
  else               return "December";
}

String DS3231::NameOfDay() {
  uint8_t V = Day();
  if (V == 1)       return "Monday";
  else if (V == 2)  return "Tuesday";
  else if (V == 3)  return "Wednesday";
  else if (V == 4)  return "Thursday";
  else if (V == 5)  return "Friday";
  else if (V == 6)  return "Saturday";
  else              return "Sunday";
}

void DS3231::TimeCal(uint8_t H0, uint8_t M0, uint8_t S0, uint8_t H1, uint8_t M1, uint8_t S1, uint8_t out[3], bool V) {
  if (V) {
    const float val = ((H0 * 60) + M0 + (S0 / 60.0)) + ((H1 * 60) + M1 + (S1 / 60.0));
    out[0] = val / 60;
    out[1] = val - (out[0] * 60);
    out[2] = round(60 * (val - ((out[0] * 60) + out[1])));
  } else {
    const float val = max(((H0 * 60) + M0 + (S0 / 60.0)), ((H1 * 60) + M1 + (S1 / 60.0))) - min(((H0 * 60) + M0 + (S0 / 60.0)), ((H1 * 60) + M1 + (S1 / 60.0)));
    out[0] = val / 60;
    out[1] = val - (out[0] * 60);
    out[2] = round(60 * (val - ((out[0] * 60) + out[1])));
  }
}

void DS3231::DateCal(int Y0, uint8_t M0, uint8_t D0, int Y1, uint8_t M1, uint8_t D1, int out[3], bool V) {
  Y0 = abs(Y0);
  Y1 = abs(Y1);
  if (0 < M0 && M0 < 13 && 0 < D0 && D0 < 32) {
    if (V) {
      const float val = ((Y0 * 12) + M0 + (D0 * 0.0328549112)) + ((Y1 * 12) + M1 + (D1 * 0.0328549112));
      out[0] = val / 12;
      out[1] = val - (out[0]  * 12);
      out[2] = round(30.4368499 * (val - ((out[0] * 12) + out[1])));
    } else {
      const float val = max(((Y0 * 12) + M0 + (D0 * 0.0328549112)), ((Y1 * 12) + M1 + (D1 * 0.0328549112))) - min(((Y0 * 12) + M0 + (D0 * 0.0328549112)), ((Y1 * 12) + M1 + (D1 * 0.0328549112)));
      out[0] = val / 12;
      out[1] = val - (out[0]  * 12);
      out[2] = round(30.4368499 * (val - ((out[0] * 12) + out[1])));
    }
  }
}

void DS3231::Return_Alarm(uint8_t month, uint8_t VV, uint8_t HH, uint8_t MM, uint8_t SS, uint8_t RT[5]) {
  if (0 < month && month < 13 && 0 < VV && VV < 32 && -1 < HH && HH < 24 && -1 < MM  && MM < 60 && -1 < SS && SS < 60) {
    uint8_t A[3];
    float V = 0;
    TimeCal(HH, MM, SS, Hour(), Minute(), Second(), A, false);
    if (HH < Hour() || (HH == Hour() && MM < Minute()) || (HH == Hour() && MM == Minute() && SS <= Second()))       TimeCal(23, 59, 59, A[0], A[1], A[2], A, 0);
    if ((HH * 24 + MM < Hour() * 24 + Minute()) | ((HH * 24 + MM == Hour() * 24 + Minute()) && (SS <= Second()))) {
      if (month < Month() || (month == Month() && VV < Date()) || (month == Month() && VV == Date() && HH < Hour()) || (month == Month() && VV == Date() && HH == Hour() && MM < Minute()) || (month == Month() && VV == Date() && HH == Hour() && MM == Minute() && SS <= Second()))  V = (month + 12 + ((VV - 1) * 0.0328549112)) - (Month() + (Date() * 0.0328549112));
      else                                                        V = (month + ((VV - 1) * 0.0328549112)) - (Month() + (Date() * 0.0328549112));
    } else {
      if (month < Month() || (month == Month() && VV < Date()) || (month == Month() && VV == Date() && HH < Hour()) || (month == Month() && VV == Date() && HH == Hour() && MM < Minute()) || (month == Month() && VV == Date() && HH == Hour() && MM == Minute() && SS <= Second()))  V = (month + 12 + ((VV) * 0.0328549112)) - (Month() + (Date() * 0.0328549112));
      else                                                        V = (month + ((VV) * 0.0328549112)) - (Month() + (Date() * 0.0328549112));
    }
    RT[0] = V;
    RT[1] = round(30.4368499 * (V - int(V)));
    if (RT[1] > 31) RT[1] = 0;
    RT[2] = A[0];
    RT[3] = A[1];
    RT[4] = A[2];
  }
}

void DS3231::Set(int YY, uint8_t MM, uint8_t DD, uint8_t HH, uint8_t mm, uint8_t SS, uint8_t WEAK) {
  YY = abs(YY);
  if (0 < MM && MM < 13 && 0 < DD && DD < 32 && -1 < HH && HH < 24 && -1 < mm  && mm < 60 && -1 < SS && SS < 60 && 0 < WEAK && WEAK < 8) {
    Wire.beginTransmission(0x68);
    Wire.write(0x0);
    Wire.write(DTB(SS));
    Wire.endTransmission(false);
    Wire.beginTransmission(0x68);
    Wire.write(0x1);
    Wire.write(DTB(mm));
    Wire.endTransmission(false);
    Wire.beginTransmission(0x68);
    Wire.write(0x2);
    Wire.write(DTB(HH));
    Wire.endTransmission(false);
    Wire.beginTransmission(0x68);
    Wire.write(0x3);
    Wire.write(DTB(WEAK));
    Wire.endTransmission(false);
    Wire.beginTransmission(0x68);
    Wire.write(0x4);
    Wire.write(DTB(DD));
    Wire.endTransmission(false);
    Wire.beginTransmission(0x68);
    Wire.write(0x5);
    Wire.write(DTB(MM));
    Wire.endTransmission(false);
    Wire.beginTransmission(0x68);
    Wire.write(0x6);
    Wire.write(DTB(YY % 100));
    Wire.endTransmission();
  }
}

void DS3231::Alarm_Write(uint8_t VV, uint8_t HH, uint8_t MM, uint8_t SS, bool Alarm) {
  uint8_t M, H, V;
  if (Alarm) {
    Wire.beginTransmission(0x68);
    Wire.write(0x7);
    Wire.write(DTB(SS));
    Wire.endTransmission(false);
    M = 0x8;
    H = 0x9;
    V = 0xA;
  } else {
    M = 0xB;
    H = 0xC;
    V = 0xD;
  }
  Wire.beginTransmission(0x68);
  Wire.write(M);
  Wire.write(DTB(MM));
  Wire.endTransmission(false);
  Wire.beginTransmission(0x68);
  Wire.write(H);
  Wire.write(DTB(HH));
  Wire.endTransmission(false);
  Wire.beginTransmission(0x68);
  Wire.write(V);
  Wire.write(DTB(VV));
  Wire.endTransmission();
}

void DS3231::Next_Alarm(bool V, uint8_t AT[4], uint8_t RT[4]) {
  Wire.beginTransmission(0x68);
  if (V)  Wire.write(0x7);
  else    Wire.write(0xB);
  Wire.endTransmission(false);
  if (V)  {
    Wire.requestFrom(0x68, 4, false);
    AT[0] = BTD(Wire.read());
  } else {
    Wire.requestFrom(0x68, 3, false);
    AT[0] = 0;
  }
  AT[1] = BTD(Wire.read());
  AT[2] = BTD(Wire.read());
  AT[3] = BTD(Wire.read());
  Return_Alarm(Month(), AT[3], AT[2], AT[1], AT[0], RT);
  Wire.requestFrom(0x68, 1);
}

void DS3231::SQW_Pin(bool BS, uint8_t SQ) {
  if (SQ < 1 || SQ > 4) SQ = 1;
  SQ -= 1;
  Wire.beginTransmission(0x68);
  Wire.write(0xE);
  Wire.endTransmission(false);
  Wire.requestFrom(0x68, 1, false);
  uint8_t V = Wire.read();
  bitWrite(V, 6, BS);
  bitWrite(V, 4, bitRead(SQ, 1));
  bitWrite(V, 3, bitRead(SQ, 0));
  bitWrite(V, 2, 0);
  Wire.beginTransmission(0x68);
  Wire.write(0xE);
  Wire.write(V);
  Wire.endTransmission();
}

void DS3231::Alarm_Interrupt(uint8_t SQ) {
  if (SQ < 1 || SQ > 4) SQ = 1;
  SQ -= 1;
  Wire.beginTransmission(0x68);
  Wire.write(0xE);
  Wire.endTransmission(false);
  Wire.requestFrom(0x68, 1, false);
  uint8_t V = Wire.read();
  bitWrite(V, 4, bitRead(SQ, 1));
  bitWrite(V, 3, bitRead(SQ, 0));
  bitWrite(V, 2, 1);
  bitWrite(V, 1, 1);
  bitWrite(V, 0, 1);
  Wire.beginTransmission(0x68);
  Wire.write(0xE);
  Wire.write(V);
  Wire.endTransmission();
}

void DS3231::SetAgingOffset(uint8_t V) {
  if (V < 0) V += 256;
  Wire.beginTransmission(0x68);
  Wire.write(0x10);
  Wire.write(V);
  Wire.endTransmission();
}

void DS3231::Oscillator(bool V) {
  Wire.beginTransmission(0x68);
  Wire.write(0xE);
  Wire.endTransmission(false);
  Wire.requestFrom(0x68, 1, false);
  uint8_t VV = Wire.read();
  bitWrite(VV, 7, V);
  Wire.beginTransmission(0x68);
  Wire.write(0xE);
  Wire.write(VV);
  Wire.endTransmission();
}

void DS3231::EN32K_Pin(bool V) {
  Wire.beginTransmission(0x68);
  Wire.write(0xF);
  if (V)  Wire.write(8);
  else    Wire.write(0);
  Wire.endTransmission();
}

bool DS3231::Alarm_State(bool V) {
  Wire.beginTransmission(0x68);
  Wire.write(0xF);
  Wire.endTransmission(false);
  Wire.requestFrom(0x68, 1);
  if (V) return bitRead(Wire.read(), 0);
  else   return bitRead(Wire.read(), 1);
}

bool DS3231::Oscillator_State() {
  Wire.beginTransmission(0x68);
  Wire.write(0xF);
  Wire.endTransmission(false);
  Wire.requestFrom(0x68, 1);
  return bitRead(Wire.read(), 7);
}

int DS3231::Year() {
  Wire.beginTransmission(0x68);
  Wire.write(0x6);
  Wire.endTransmission(false);
  Wire.requestFrom(0x68, 1);
  uint8_t V = BTD(Wire.read());
  if (V == 99)  Year100 = true;
  if (Year100 && V == 0) {
    Year100 = false;
    _Year += 100;
  }
  return _Year + V;
}