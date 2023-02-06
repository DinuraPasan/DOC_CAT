//  Produced by Dinura Pasan in February 2023 and distributed free of charge.
//  Controlling the DS3231 RTC IC from within the Arduino environment.
//  Source Code --> https://github.com/DinuraPasan/DOC_CAT/
//  Two time calculation.

#include <DOC_CAT.h>
DS3231 RTC(21);  //  Syntax(uint8_t Current_century)
int A[3];
uint8_t B[4];

void setup() {
  Serial.begin(9600);
  //  --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  //  | void DateCal(int Year_1, uint8_t Month_1, uint8_t Date_1, int Year_2, uint8_t Month_2, uint8_t Date_2, int Return_time[3], boolean state)  -- return_format -- > YY / MM / DD             |
  //  | void TimeCal(uint8_t Hour_1, uint8_t Minute_1, uint8_t Second_1, uint8_t Hour_2, uint8_t Minute_2, uint8_t Second_2, int Return_time[3], boolean state)  -- return_format -- > HH: MM: SS |
  //  | void Return_Alarm(uint8_t month, uint8_t VV, uint8_t HH, uint8_t MM, uint8_t SS, uint8_t RT[5])   -- return_format -- > DD: HH: MM: SS                                                    |
  //  | String Weekday(int Year, uint8_t Month, uint8_t Date)                                                                                                                                     |
  //  | float Converter(uint8_t type, float value)                                                                                                                                                |
  //  --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

  // Adding two days
  RTC.DateCal(2020, 01, 01, 10, 05, 04, A, true);
  Serial.print("Date_1(2020/01/01) + Date_2(10/05/04) == ");
  Serial.println(String(A[0]) + "/" + String(A[1]) + "/" + String(A[2]));
  // Two days subtract
  RTC.DateCal(2020, 01, 01, 2010, 05, 04, A, false);
  Serial.print("Date_1(2020/01/01) - Date_2(2010/05/04) == ");
  Serial.println(String(A[0]) + "/" + String(A[1]) + "/" + String(A[2]));
  // Adding time days
  RTC.TimeCal(10, 10, 10, 10, 10, 12, B, true);
  Serial.print("Time_1(10:10:10) + Time_2(10:10:12) == ");
  Serial.println(String(B[0]) + ":" + String(B[1]) + ":" + String(B[2]));
  // Two time subtract
  RTC.TimeCal(10, 10, 10, 10, 10, 12, B, false);
  Serial.print("Time_1(10:10:10) - Time_2(10:10:12) == ");
  Serial.println(String(B[0]) + ":" + String(B[1]) + ":" + String(A[2]));
  // Print a weekday serial monitor
  Serial.print("2020/12/5 -- ");
  Serial.println(RTC.Weekday(2020, 12, 5));
  // Converter to Second to minute
  Serial.print("100 seconds convert to minutes  == ");
  Serial.println(RTC.Converter(00, 100));
  // Alarm On time return
  RTC.Return_Alarm(RTC.Month(), RTC.Date(), RTC.Hour(), 55, 40, B);
  Serial.print("Alarm On Time :- ");
  Serial.println(String(B[0]) + ":" + String(B[1]) + ":" + String(A[2]) + ":" + String(A[3]));
  //  ----DS3231 Converter Function Details------------
  //  | Converter(uint8_t V, float value)              |
  //  | ------Value converter to reverse---------------
  //  | V == 00 -- > sec > min                         |
  //  | V == 01 -- > sec > hour                        |
  //  | V == 02 -- > sec > day                         |
  //  | V == 03 -- > sec > weeks                       |
  //  | V == 04 -- > sec > month                       |
  //  | V == 05 -- > sec > year                        |
  //  | V == 06 -- > min > sec                         |
  //  | V == 07 -- > min > hour                        |
  //  | V == 08 -- > min > day                         |
  //  | V == 09 -- > min > weeks                       |
  //  | V == 10 -- > min > month                       |
  //  | V == 11 -- > min > year                        |
  //  | V == 12 -- > hour > sec                        |
  //  | V == 13 -- > hour > min                        |
  //  | V == 14 -- > hour > day                        |
  //  | V == 15 -- > hour > weeks                      |
  //  | V == 16 -- > hour > month                      |
  //  | V == 17 -- > hour > year                       |
  //  | V == 18 -- > day > sec                         |
  //  | V == 19 -- > day > min                         |
  //  | V == 20 -- > day > hour                        |
  //  | V == 21 -- > day > weeks                       |
  //  | V == 22 -- > day > month                       |
  //  | V == 23 -- > day > year                        |
  //  | V == 24 -- > weeks > sec                       |
  //  | V == 25 -- > weeks > min                       |
  //  | V == 26 -- > weeks > hour                      |
  //  | V == 27 -- > weeks > day                       |
  //  | V == 28 -- > weeks > month                     |
  //  | V == 29 -- > weeks > year                      |
  //  | V == 30 -- > month > sec                       |
  //  | V == 31 -- > month > min                       |
  //  | V == 32 -- > month > hour                      |
  //  | V == 33 -- > month > day                       |
  //  | V == 34 -- > month > weeks                     |
  //  | V == 35 -- > month > year                      |
  //  | V == 36 -- > year > sec                        |
  //  | V == 37 -- > year > min                        |
  //  | V == 38 -- > year > hour                       |
  //  | V == 39 -- > year > day                        |
  //  | V == 40 -- > year > weeks                      |
  //  | V == 41 -- > year > month                      |
  //  -------------------------------------------------
}

void loop() {}