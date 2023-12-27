#include "pzhelp"

PROGRAM{
  int  j, u, a;
  j = READ_INT();
  u = READ_INT();
a = j + u;
  if ( a % 100 == 42)
    WRITELN ("yes");
  else WRITELN ("no");
}