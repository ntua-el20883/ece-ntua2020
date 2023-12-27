#include "pzhelp"
PROGRAM {
  int a, b, c;
  a = READ_INT();
  b = a / 100000;
  c = a % 10;
  if (b == c)
    WRITELN ("yes");
  else WRITELN ("no");
}