#include "pzhelp"
PROC hello () {
    WRITELN("hello world");}
    PROGRAM { int n, i;
        n = READ_INT();
        if (n <= 0) WRITELN ("nothing today");
        else FOR(i, 1 TO n) hello();}
