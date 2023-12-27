#include "pzhelp"

PROGRAM {
  int j, u, a;
    j = READ_INT();
  u = j % 10;
  a = j / 10;
  if (u == 7 AND a == 7)
    WRITELN ("2");
  else if ( u == 7 OR a == 7)
    WRITELN ("1");
  else WRITELN ("0");
}