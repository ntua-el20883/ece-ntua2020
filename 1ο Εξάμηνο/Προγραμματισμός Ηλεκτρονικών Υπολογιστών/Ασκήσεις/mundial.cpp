#include "pzhelp"
PROGRAM {
  int j, u;
  j = READ_INT();
  u = (j - 1930) % 4;
    if (j == 1942 OR j == 1946)
      WRITELN ("no");
    else if (j < 1930)
      WRITELN ("no");
    else if ( u == 0)
      WRITELN ("yes");
    else WRITELN ("no");
}