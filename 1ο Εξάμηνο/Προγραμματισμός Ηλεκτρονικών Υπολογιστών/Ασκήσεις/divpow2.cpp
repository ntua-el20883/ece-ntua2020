#include "pzhelp"
PROGRAM {
  int n;
  int i;
  n = READ_INT();
  i = 0;
  while (n % 2 == 0)
 {
   n = n / 2;
   i = i + 1;
 }
 WRITELN (i);
}