#include "pzhelp"
PROGRAM {
  int M, N, j;
  M = READ_INT();
  N = READ_INT();
  j = M*N;
  if (j>999 AND j<10000)
    WRITELN ("yes");
  else WRITELN("no");
}