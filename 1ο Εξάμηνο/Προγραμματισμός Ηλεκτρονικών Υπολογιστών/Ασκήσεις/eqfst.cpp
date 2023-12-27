#include "pzhelp"
PROGRAM {
  REAL j, u, a;
  j = READ_REAL();
  u  = READ_REAL();
  if ( j != 0.0){
    a = -u/j;
    if (a == 0.0) a = 0.0;
    WRITELN ( FORM ( a, 0, 6));
  }
  else if ( u != 0.0)
    WRITELN ("impossible");
  else WRITELN ("trivial");
}