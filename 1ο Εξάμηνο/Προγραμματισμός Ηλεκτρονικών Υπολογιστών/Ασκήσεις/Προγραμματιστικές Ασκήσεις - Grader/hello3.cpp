#include "pzhelp"
PROC hello () {
    WRITELN("hello world");
    }
    PROGRAM {
        int i;
        FOR(i, 1 TO 20) hello();
        }
