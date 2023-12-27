#include "pzhelp"
PROGRAM {
  int a, b;
  a = READ_INT();
  b = READ_INT();
  if ((a % 17 == 0) AND (b % 42 == 0))
    WRITELN ("yes");
  else if ((b % 17 == 0) AND (a % 42 == 0))
    WRITELN ("yes");
  else WRITELN ("no");
}
