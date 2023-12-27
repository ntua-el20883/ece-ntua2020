#include "pzhelp"
PROGRAM {
  REAL a, b, c, d, e, f, g, h, i;
  a = READ_REAL();
  b = READ_REAL();
  c = READ_REAL();
  d = abs(a - b);
  e = a + b;
  f = abs(a - c);
  g = a + c;
  h = abs(c - b);
  i = c + b;

 if (d < c AND c < e)
   WRITELN ("yes");

 else if (f < b AND b < g)
  WRITELN ("yes");

 else if (h < a AND a < i)
   WRITELN ("yes");

 else WRITELN ("no");
}