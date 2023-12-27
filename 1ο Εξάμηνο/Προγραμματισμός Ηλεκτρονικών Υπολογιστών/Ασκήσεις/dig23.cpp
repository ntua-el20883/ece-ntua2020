#include "pzhelp"
PROGRAM {
  int a, b, c;
  a = READ_INT();
  b = READ_INT();
  c = a*b;
  c = c / 10;
  c = c % 100;
  printf("%02d\n", c);
  }