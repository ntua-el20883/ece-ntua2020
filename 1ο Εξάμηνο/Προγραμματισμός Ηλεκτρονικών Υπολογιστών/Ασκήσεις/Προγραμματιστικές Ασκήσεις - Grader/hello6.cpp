#include "pzhelp"
PROC hello () {
    WRITELN("hello world");
    }
    PROGRAM {
        int n, i;
        WRITE("Give number of greetings then press <enter>: ");
        n = READ_INT();
        if (n < 0) WRITELN("The number", n, "is negative");
        else  FOR(i, 1 TO n) hello();
        }
