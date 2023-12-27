#include "pzhelp"

PROGRAM
{
  int a, b, c, d, t, i, num, den, in, gcd, numh, denh;
  char op;

  t = READ_INT();

  FOR (i, 1 TO t) {

  SKIP_LINE();
  op = getchar();
  a = READ_INT();
  b = READ_INT();
  c = READ_INT();
  d = READ_INT();


  if ((b == 0) OR (d == 0) OR ((c == 0) AND (op == '/')))
    WRITELN ("error");


  else {
    switch (op)
    {
      case '+': num = (a*d + c*b);
                den = (b*d); break;

      case '-': num = (a*d - c*b);
                den = (b*d); break;

      case '*': num = (a*c);
                den = (b*d); break;

      case '/': num = (a*d);
                den = (b*c); break;
     }//switch

   if (num != 0)
   {
    numh = abs(num);
    denh = abs(den);
    while (numh > 0 AND denh > 0)
    {
      if (numh > denh) numh = numh % denh;
      else denh = denh % numh;
      gcd = numh + denh;
    } //while
   num = num/gcd;
   den = den/gcd;
   in = num/den;
   num = num - in*den;

   if (in == 0 AND num < 0 AND den > 0) WRITELN("-0", abs(num), den);
   else if (in == 0 AND num > 0 AND den < 0) WRITELN("-0", num, abs(den));
   else if (in < 0) { num = abs(num);  den = abs(den); WRITELN(in, num, den); }
   else if (in == 0 AND num == 0) WRITELN ("0 0 1");
   else if (in != 0 AND num == 0) WRITELN (in,num, abs(den));
   else if (num < 0 AND den < 0) WRITELN (in, abs(num), abs(den));
   else WRITELN (in, num, den);
   }//if

   else WRITELN("0 0 1");

  }//else
 }//FOR
}//PROGRAM