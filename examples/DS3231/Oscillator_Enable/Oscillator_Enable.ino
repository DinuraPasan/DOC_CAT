//  Produced by Dinura Pasan in February 2023 and distributed free of charge.
//  Controlling the DS3231 RTC IC from within the Arduino environment.
//  Source Code --> https://github.com/DinuraPasan/DOC_CAT/
//  DS3231 IC SQW, 32KHz pin and Aging Offset buffer control.

#include <DOC_CAT.h>
DS3231 RTC(21);  //  Syntax(uint8_t Current_century)

void setup() {
  Serial.begin(9600);
  RTC.Oscillator(true);                    // Oscillator on or Off
  Serial.println(RTC.Oscillator_State());  // Returns false if the oscillator has been off for some reason. if this is the case, the time is probably not correct
  RTC.EN32K_Pin(true);                     // Enable the 32KHz pin
  RTC.EN32K_Pin(false);                    // Disable the 32KHz pin
  // Enable the SQW pin
  RTC.SQW_Pin(true, 1);  // Syntax(bool Battery_Backed, uint8_t frequency)
  //  ------Frequency Range----
  //  |   1   1Hz              |
  //  |   2   1.024KHz         |
  //  |   3   4.096KHZ         |
  //  |   4   8.192KHZ         |
  //  -------------------------

  //  Aging Offset Control function
  //  RTC.SetAgingOffset(10);                   // Set the Aging Offset value
  //  Serial.println(RTC.GetAgingOffset());     // Get the Aging Offset value
}

void loop() {}