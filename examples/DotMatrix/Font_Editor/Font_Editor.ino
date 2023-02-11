//  Produced by Dinura Pasan in February 2023 and distributed free of charge.
//  Controlling the LED Dot Matrix from within the Arduino environment.
//  Source Code --> https://github.com/DinuraPasan/DOC_CAT/

//  The DotMatrix library does not write to the LED Matrix Driver IC.
//  Assign the library data source to the LED Matrix Driver IC write function you are using.
//  DotMatrix library compatible with any LED Matrix Driver IC.
//  But the LED Matrix Driver IC write function must be developed by the user. (help :- Use the LED Matrix Driver IC Datasheet)

//           0----------------------+...9
//           |  ----------------------->Y
//           |  |
//           |  |
//           |  |
//           |  |
//           |  |
//           |  |
//           |  |
//           +  |
//           .  |
//           .  |
//           . \|/
//           9  X

//  Array Size ==> if((X Axis LED * Y Axis LED)/8 == 0) { Array Size = (X Axis LED * Y Axis LED)/8 }
//  Array Size ==> if((X Axis LED * Y Axis LED)/8 != 0) { Array Size = (X Axis LED * Y Axis LED)/8+1 }
byte data[8];

#include <DOC_CAT.h>
DotMatrix Matrix(8, 8, data);  // Syntax(int X_Axis_LED, int Y_Axis_LED, byte Return_data_array)

byte S[]{
  B00000001,
  B00000010,
  B00000100,
  B00001000,
  B00010000,
  B00100000,
  B01000000,
  B10000000
};

int M[] = { 8, 8, 1, 8, 0, 0, 0, 0 };  // Parameter(Display_Width, Display_Height, Array_Width_for_bytes, Array_Height, Start_X, Start_Y, Move_X, Move_Y)

void setup() {}

void loop() {
  // User defined font write
  Matrix.Dotset(true, M, S);  // Syntax(bool type, int[], byte[])
  write();
}

void write() {
  // Use the DotMatrix library data array and write the Driver IC function
}