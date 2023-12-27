#include "pzhelp"
PROGRAM {
  int a;
  a = READ_INT();
  if ( a > 9 AND a < 100)
    WRITELN ("yes");
  else if ( a > 999 AND a < 10000)
    WRITELN ("yes");
  else if ( a > 99999 AND a < 100000)
    WRITELN ("yes");
  else WRITELN ("no");
}