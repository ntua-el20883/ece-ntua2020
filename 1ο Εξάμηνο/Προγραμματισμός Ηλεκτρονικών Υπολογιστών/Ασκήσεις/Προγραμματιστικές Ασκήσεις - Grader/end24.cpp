#include "pzhelp"

PROGRAM {
  int j;
  j = READ_INT();
  j =( j * j);
    if (j % 100 == 24)
      WRITELN ("yes");
    else WRITELN ("no");
}