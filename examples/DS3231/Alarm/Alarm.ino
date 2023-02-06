//  Produced by Dinura Pasan in February 2023 and distributed free of charge.
//  Controlling the DS3231 RTC IC from within the Arduino environment.
//  Source Code --> https://github.com/DinuraPasan/DOC_CAT/
//  Alarm function.

#include <DOC_CAT.h>
DS3231 RTC(21);  //  Syntax(uint8_t Current_century)
uint8_t A[4], B[4];

void setup() {
  Serial.begin(9600);
  // DS3231 Set the IC real time
  RTC.Set(2020, 01, 01, 00, 00, 00, 3);  //  Syntax(int Year, uint8_t Month, uint8_t Date, uint8_t Hour, uint8_t Minute, uint8_t Second, uint8_t Day)
}

void loop() {
  //  ------Frequency Range----
  //  |   1   1Hz              |
  //  |   2   1.024KHz         |
  //  |   3   4.096KHZ         |
  //  |   4   8.192KHZ         |
  //  -------------------------
  RTC.Alarm_Interrupt(1);                  //  Set the DS3231SQW pin Output frequency
  RTC.Alarm_Write(10, 00, 01, 50, true);   //  Write the 1st alarm for the DS3231
  RTC.Alarm_Write(12, 00, 00, 00, false);  //  Write the 2nd alarm for the DS3231
  B[0] = 10;
  B[0] = 00;
  B[0] = 01;
  B[0] = 50;
  RTC.Next_Alarm(true, B, A);
  Serial.print("1st Alarm ON time:-  ");
  Serial.println(String(A[3]) + ":" + String(A[2]) + ":" + String(A[1]) + ":" + String(A[0]));
  B[0] = 12;
  B[0] = 00;
  B[0] = 00;
  B[0] = 00;
  RTC.Next_Alarm(true, B, A);
  Serial.print("2nd Alarm ON time:-  ");
  Serial.println(String(A[3]) + ":" + String(A[2]) + ":" + String(A[1]) + ":" + String(A[0]));
  if (RTC.Alarm_State(true)) Serial.println("Alarm One Is ON");   //  Check the 1st alarm state
  if (RTC.Alarm_State(false)) Serial.println("Alarm Two Is ON");  //  Check the 2nd alarm state

  //  ------Alarm Function  -----------------------------------------------------------------------------------------------------------------------------------------------------------
  //  | void Alarm_Write(uint8_t Day, uint8_t HH, uint8_t MM, uint8_t SS, bool Alarm)                                                                                                  |
  //  | void Return_Alarm(uint8_t month, uint8_t Day, uint8_t HH, uint8_t MM, uint8_t SS, uint8_t Return_time[5])    return_format -- > DD/ HH: MM: SS                                 |
  //  | void Next_Alarm(bool V, uint8_t Alarm_time[4], uint8_t Return_time[4])                                       return_format -- > DD/ HH: MM: SS(return_format == Input_format)  |
  //  | void Alarm_Interrupt(uint8_t SQ)                                                                                                                                               |
  //  | bool Alarm_State(bool V)                                                                                                                                                       |
  //  ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
}