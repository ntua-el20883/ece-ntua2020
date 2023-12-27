#include "pzhelp"
PROGRAM
{
  int n, p, i;
  n = READ_INT();
  p = 1;
  FOR (i, 1 TO 200)
  {
    p = p * i;
    if (p > n)
    {
  WRITELN (i - 1);
  break;
    }
 }
}