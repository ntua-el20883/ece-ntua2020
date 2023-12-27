#include "pzhelp"
const int n = 20;
int i;
PROC num_hello () {
    WRITELN(i, "hello world");
    }
    PROGRAM {
        FOR(i, 1 TO n) num_hello();
        }
