//  Produced by Dinura Pasan in February 2023 and distributed free of charge.
//  Controlling the LED Dot Matrix from within the Arduino environment.
//  Source Code --> https://github.com/DinuraPasan/DOC_CAT/

#include <Arduino.h>
#include <EEPROM.h>
#include <DOC_CAT.h>

DotMatrix::DotMatrix(int X, int Y, uint8_t *A) {
  _X = X;
  _Y = Y;
  _A = A;
}

void DotMatrix::Set(int x, int y, bool type) {
  if (_X > x && 0 <= x && _Y > y && 0 <= y && _X > 0 && _Y > 0)   bitWrite(_A[((y * _Y) + x) / 8], ((y * _Y) + x) % 8, type);
}

void DotMatrix::SetAll(bool type) {
  for (int y = 0; y < _Y; y++) {
    for (int x = 0; x < _X; x++) {
      Set(x, y, type);
    }
  }
}

void DotMatrix::Dotset(bool type, int DD[8], byte val[]) {
  if (DD[0] > 0 && DD[1] > 0 && DD[2] > 0 && DD[3] > 0) {
    for (int DH = 0; DH < DD[1]; DH++) {
      for (int DW = 0; DW < DD[0]; DW++) {
        int index = (((DD[7] + DH) * (DD[2] * 8)) + DW + DD[6]);
        if ((DH + DD[7] >= DD[3]) || (DH + DD[7] < 0) || (DW + DD[6] >= (DD[2] * 8)) || (DW + DD[6] < 0)) {
          Set(DW + DD[4], DH + DD[5], !type);
        } else {
          if (type == true) Set(DW + DD[4], DH + DD[5], bitRead(val[index / 8], (index % 8)));
          else              Set(DW + DD[4], DH + DD[5], !bitRead(val[index / 8], (index % 8)));
        }
      }
    }
  }
}

void DotMatrix::Text(char T[], bool type, int D[6]) {
  byte V[strlen(T) * 8];
  int DD[8] = {D[0], D[1], strlen(T), 8, D[2], D[3], D[4], D[5]};
  int index = 0;
  for (int t = 0; t < strlen(T); t++) {
    for (int k = 0; k <= 94; k++) {
      if (T[t] == char(EEPROM.read(k))) {
        index = t;
        for (int e = 95 + (k * 8); e < 95 + (( k + 1) * 8); e++) {
          V[index] = EEPROM.read(e);
          index = index + strlen(T);
        }
      }
    }
  }
  Dotset(type, DD, V);
}

void DotMatrix::Line(int x, int y, int xx, int yy, bool type) {
  if (x == xx) {
    for (int i = (min(y, yy)); i <= max(y, yy); i++) {
      Set(x, i, type);
    }
  } else {
    float xy = xx;
    float m = (((y) - (yy)) / ((x) - (xy)));
    float c = y - (m * x);
    for (int i = (min(x, xx)); i <= max(x, xx); i++) {
      int b = round((m * i) + c);
      Set(i, b, type);
    }
  }
}

void DotMatrix::Rect(int x, int y, int width, int height, bool outline, bool colour) {
  for (int i = y; i <= y + height; i++) {
    Line(x, i, x + width, i, colour);
  }
  Line(x, y, x + width, y, outline);
  Line(x + width, y, x + width, y + height, outline);
  Line(x + width, y + height, x, y + height, outline);
  Line(x, y + height, x, y, outline);
}

void DotMatrix::Circle(int x, int y, int r, bool outline, bool colour) {
  for (int i = 0; i <= r; i++) {
    float a = sqrt(sq(r) - sq(i));
    int yy = round(a);
    Line(x - i, y - yy, x - i, y + yy, colour);
    Line(x + i, y - yy, x + i, y + yy, colour);
    Set(x - i, y - yy, outline);
    Set(x + i, y - yy, outline);
    Set(x - i, y + yy, outline);
    Set(x + i, y + yy, outline);
  }
}

void DotMatrix::Trangale(int x, int y, int xx, int yy, int xxx, int yyy, bool outline) {
  Line(x, y, xx, yy, outline);
  Line(x, y, xxx, yyy, outline);
  Line(xx, yy, xxx, yyy, outline);
}