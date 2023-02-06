//  Produced by Dinura Pasan in February 2023 and distributed free of charge.
//  Controlling the 74HC595 shift registers IC from within the Arduino environment.
//  Source Code --> https://github.com/DinuraPasan/DOC_CAT/
//  Control Sevensegment display with 74HC595 IC.

//                        ----Circuit Diagram----

//      |¯ ¯ 0 ¯ ¯|      |¯ ¯ 0 ¯ ¯|      |¯ ¯ 0 ¯ ¯|      |¯ ¯ 0 ¯ ¯|
//      5         1      5         1      5         1      5         1
//      |         |      |         |      |         |      |         |
//      |_ _ 6 _ _|      |_ _ 6 _ _|      |_ _ 6 _ _|      |_ _ 6 _ _|
//      |         |      |         |      |         |      |         |
//      4         2      4         2      4         2      4         2
//      |         |      |         |      |         |      |         |
//      |_ _ 3 _ _| •7   |_ _ 3 _ _| •7   |_ _ 3 _ _| •7   |_ _ 3 _ _| •7
//       Comman 01        Comman 02        Comman 03        Comman 04

//                   ST_ SH_                       ST_ SH_
//        +  Q0 DS OE CP CP MR QH       +  Q0 DS OE CP CP MR QH
//        |  |  |  |  |  |  |  |        |  |  |  |  |  |  |  |
//        |__|__|__|__|__|__|__|        |__|__|__|__|__|__|__|
//        |                    |        |                    |
//        |    74HC595 IC 01   |        |    74HC595 IC 02   |
//        | •                  |        | •                  |
//        |__ __ __ __ __ __ __|        |__ __ __ __ __ __ __|
//        |  |  |  |  |  |  |  |        |  |  |  |  |  |  |  |
//        |  |  |  |  |  |  |  |        |  |  |  |  |  |  |  |
//        Q1 Q2 Q3 Q4 Q5 Q6 Q7 GND      Q1 Q2 Q3 Q4 Q5 Q6 Q7 GND

//                        ----Pin Management----

//  IC 01   Q0      -- >       All Sevensegment Display 00
//  IC 01   Q1      -- >       All Sevensegment Display 01
//  IC 01   Q2      -- >       All Sevensegment Display 02
//  IC 01   Q3      -- >       All Sevensegment Display 03
//  IC 01   Q4      -- >       All Sevensegment Display 04
//  IC 01   Q5      -- >       All Sevensegment Display 05
//  IC 01   Q6      -- >       All Sevensegment Display 06
//  IC 01   Q7      -- >       All Sevensegment Display 07
//  IC 02   Q0      -- >       Sevensegment Display Comman 01
//  IC 02   Q1      -- >       Sevensegment Display Comman 02
//  IC 02   Q2      -- >       Sevensegment Display Comman 03
//  IC 02   Q3      -- >       Sevensegment Display Comman 04

uint8_t SER = 10;     // pin 14 on the 74HC595  outher name DS pin(data pin)
uint8_t RCLK = 11;    // pin 12 on the 74HC595  outher name ST_CP pin(latch pin)
uint8_t SRCLK = 12;   // pin 11 on the 74HC595  outher name SH_CP pin(clock pin)
uint8_t NUMOFIC = 2;  // Number of IC

#include <DOC_CAT.h>
HC74595 Shift(NUMOFIC, SER, RCLK, SRCLK);

void setup() {}

void loop() {
  // loop function not add the delay time.
  // Syntax(uint8_t valve, uint8_t Start_display_number_place, int Max_display_count, boolean type(type == true --> common anode /// type == false --> common cathode))
  Shift.Sevensegment(B01011101, 0, 4, true);
  // Syntax(double valve, uint8_t Start_display_number_place, int Max_display_count, boolean type(type == true --> common anode /// type == false --> common cathode))
  Shift.SegmentNumber(-2.1, 1, 4, true);
  // Syntax(int valve, uint8_t Start_display_number_place, int Max_display_count, boolean type(type == true --> common anode /// type == false --> common cathode))
  Shift.SegmentNumber(145, 1, 4, true);
}