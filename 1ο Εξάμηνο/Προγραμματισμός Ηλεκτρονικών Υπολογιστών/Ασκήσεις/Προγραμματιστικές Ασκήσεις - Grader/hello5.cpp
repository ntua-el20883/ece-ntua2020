#include "pzhelp"
PROC hello () {
    WRITELN("hello world");
    }
    PROGRAM {
        int n, i;
        WRITE("Give number of greetings",
              "then press <enter>: ");
              n = READ_INT();
              FOR(i, 1 TO n)
              hello();
              }
