#include "pzhelp"

PROGRAM {

  int j, u, a, n;

 j = READ_INT();
 u = READ_INT();
 a = READ_INT();
 n = READ_INT();

 WRITE((j*n) + (u*a));
 WRITE(" ");
 WRITE(u*n);
}