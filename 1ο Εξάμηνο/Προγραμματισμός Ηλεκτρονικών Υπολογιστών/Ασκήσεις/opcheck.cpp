#include "pzhelp"
PROGRAM
{
  int a, b, c, i;
  char op, eq;

  FOR (i, 1 TO 5)
  {
  a = READ_INT();
  op = getchar();
  b = READ_INT();
  eq = getchar();
  c = READ_INT();

  switch (op)
   {
    case '+': if (a+b == c) WRITELN ("correct");
                else WRITELN("wrong"); break;
    case '-': if (a-b == c) WRITELN ("correct");
                else WRITELN("wrong"); break;
    case '*': if (a*b == c) WRITELN("correct");
                else WRITELN("wrong"); break;
    case '/': if (a/b == c) WRITELN("correct");
                else WRITELN("wrong"); break;
    case '%': if (a%b == c) WRITELN("correct");
                  else WRITELN("wrong"); break;
   }
  }
}
