#include "pzhelp"
PROGRAM {
  int j, u, a;
  j = READ_INT();
  u = READ_INT();
  a = READ_INT();

  if (u>a AND j>a)
    WRITELN(a);
  else if (u>j AND a>j)
    WRITELN(j);
  else if (u == j AND u == a)
    WRITELN(u);
  else if (j>u AND a>u)
    WRITELN(u);
  else if (j == u AND j < a)
    WRITELN(j);
  else if (j == u AND j > a)
    WRITELN(a);
  else if (j == a AND j < u)
    WRITELN(j);
  else if (j == a AND j > u)
    WRITELN(u);
  else if (u == a AND u < j)
    WRITELN(u);
  else if (u == a AND u > j)
    WRITELN(j);
}