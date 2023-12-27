#include "pzhelp"

PROGRAM {
  int j, u, a;
  j = READ_INT();
  u = READ_INT();
  a = READ_INT();

  j = (j % 42);
  u = (u % 42);
  a = (a % 42);

  if ( j == u AND u == a )
    WRITELN (a);
  else WRITELN ("no");
}