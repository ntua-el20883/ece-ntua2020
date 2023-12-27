#include "pzhelp"

PROGRAM {
  int j;
  j = READ_INT();
  if (j > 99  AND j < 1000)
    WRITELN ("yes");
  else WRITELN ("no");
}