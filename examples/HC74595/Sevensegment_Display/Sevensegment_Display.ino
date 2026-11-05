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

uint8_t SER = 10;     // Arduino pin connected to pin 14 (DS / data) of the 74HC595.
uint8_t RCLK = 11;    // Arduino pin connected to pin 12 (ST_CP / latch) of the 74HC595.
uint8_t SRCLK = 12;   // Arduino pin connected to pin 11 (SH_CP / clock) of the 74HC595.
uint8_t NUMOFIC = 2;  // Number of cascaded 74HC595 ICs.

#include <DOC_CAT.h>
HC74595 Shift(NUMOFIC, SER, RCLK, SRCLK);

void setup() {}

void loop() {
  // Display a custom segment pattern on the selected digit.
  // Syntax: Sevensegment(uint8_t segments, uint8_t digitPosition, uint8_t digitCount, bool commonAnode).
  // The binary value determines which segments are illuminated.
  Shift.Sevensegment(B01011101, 0, 4, true);

  // Display a floating-point number, including decimal points and negative signs.
  // Syntax: SegmentNumber(double value, uint8_t digitPosition, uint8_t digitCount, bool commonAnode).
  Shift.SegmentNumber(-2.1, 1, 4, true);

  // Display an integer number on the multiplexed seven-segment display.
  // Syntax: SegmentNumber(int value, uint8_t digitPosition, uint8_t digitCount, bool commonAnode).
  Shift.SegmentNumber(145, 1, 4, true);
}