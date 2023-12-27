#include "pzhelp"

PROGRAM {
  int j, u;
  j = READ_INT();
  u =  READ_INT();
  if (j % 2 == 0  AND u % 2 == 0)
    WRITELN ("2");
  else if (j % 2 ==0 OR u % 2 ==0 )
    WRITELN ("1");
  else WRITELN ("0");
}