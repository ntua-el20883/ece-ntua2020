#include "pzhelp"
PROGRAM {
  int j, u ;
  j = READ_INT ();
  u = READ_INT ();
  if (j > u)
    WRITELN (j);
  else WRITELN (u);
}