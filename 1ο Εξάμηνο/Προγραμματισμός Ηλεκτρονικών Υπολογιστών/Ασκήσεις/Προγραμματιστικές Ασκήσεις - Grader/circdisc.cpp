#include "pzhelp"
PROGRAM {
  REAL  x, y, d;
  x = READ_REAL();
  y = READ_REAL();
  d = sqrt ((x*x) + (y*y));
    if (d < 1)
      WRITELN ("inside");
    else if (d == 1)
      WRITELN ("border");
    else WRITELN ("outside");
}