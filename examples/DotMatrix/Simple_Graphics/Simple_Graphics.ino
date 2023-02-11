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

void setup() {}

void loop() {
  // Display line on LED Display
  Matrix.Line(0, 0, 5, 5, true);  // Syntax(int x, int y, int xx, int yy, bool outline)
  write();
  // Display rectangle on LED Display
  Matrix.Rect(0, 0, 4, 4, true, false);  // Syntax(int x, int y, int width, int height, bool outline, bool colour)
  write();
  // Display circle on LED Display
  Matrix.Circle(3, 3, 3, true, false);  // Syntax(int x, int y, int r, bool outline, bool colour)
  write();
  // Display Triangle on LED Display
  Matrix.Trangale(0, 0, 0, 7, 7, 7, true);  // Syntax(int x, int y, int xx, int yy, int xxx, int yyy, bool outline)
  write();
  // Display one LED on LED Display
  Matrix.Set(0, 0, true);  // Syntax(int x, int y, bool type)
  write();
  // Display all LED on LED Display
  Matrix.SetAll(true);  // Syntax(bool type)
  write();
}

void write() {
  // Use the DotMatrix library data array and write the Driver IC function
}