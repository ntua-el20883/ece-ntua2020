#include "pzhelp"

PROGRAM {
  int j;
  j  = READ_INT();
  if (j % 7 == 0 AND j % 6 != 0)
  WRITELN ("yes");
  else WRITELN ("no");
}