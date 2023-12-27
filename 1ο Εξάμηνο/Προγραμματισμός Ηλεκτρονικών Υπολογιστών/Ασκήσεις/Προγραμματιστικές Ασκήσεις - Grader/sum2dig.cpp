#include "pzhelp"
PROGRAM {
  int a, b, c, d;
  a = READ_INT();
  b = a % 10;
  c = (a % 100) / 10;
  d = b + c;
  WRITELN(d);
}