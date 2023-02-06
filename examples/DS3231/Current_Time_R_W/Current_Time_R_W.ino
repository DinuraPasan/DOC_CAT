//  Produced by Dinura Pasan in February 2023 and distributed free of charge.
//  Controlling the DS3231 RTC IC from within the Arduino environment.
//  Source Code --> https://github.com/DinuraPasan/DOC_CAT/
//  Current Time and Date DS3231 IC write and read.
//  DS3231 IC internal temperature reading.

#include <DOC_CAT.h>
DS3231 RTC(21);  // Syntax(uint8_t Current_century)

void setup() {
  Serial.begin(9600);
  // DS3231 Set the IC real time
  RTC.Set(2020, 01, 01, 00, 00, 00, 3);  // Syntax(int Year, uint8_t Month, uint8_t Date, uint8_t Hour, uint8_t Minute, uint8_t Second, uint8_t Day)
  //  --Day Number  -------------
  //  | Day == 1 -- > Monday    |
  //  | Day == 2 -- > Tuesday   |
  //  | Day == 3 -- > Wednesday |
  //  | Day == 4 -- > Thursday  |
  //  | Day == 5 -- > Friday    |
  //  | Day == 6 -- > Saturday  |
  //  | Day == 7 -- > Sunday    |
  //  ---------------------------
}

void loop() {
  // Print the time of serial monitor
  Serial.print("Date:-  ");
  Serial.print(String(RTC.Year()) + "/" + String(RTC.Month()) + "/" + String(RTC.Date()) + "  " + RTC.NameOfMonth());
  Serial.print("        ");
  // Print the time of serial monitor
  Serial.print("Time:-  ");
  Serial.print(String(RTC.Hour()) + ":" + String(RTC.Minute()) + ":" + String(RTC.Second()) + "  " + String(RTC.Day()) + "  " + RTC.NameOfDay());
  Serial.print("        ");
  // Print the internal temperature of the DS3231 on the serial monitor
  Serial.print("Temperature:-  ");
  Serial.println(RTC.Temperature());

  //  --Function Return Type  ---------
  //  | int Year();                   |
  //  | uint8_t Month();              |
  //  | uint8_t Date();               |
  //  | uint8_t Hour();               |
  //  | uint8_t Minute();             |
  //  | uint8_t Second();             |
  //  | uint8_t Day();                |
  //  | String NameOfMonth();         |
  //  | String NameOfDay();           |
  //  | float Temperature()           |
  //  ---------------------------------
}