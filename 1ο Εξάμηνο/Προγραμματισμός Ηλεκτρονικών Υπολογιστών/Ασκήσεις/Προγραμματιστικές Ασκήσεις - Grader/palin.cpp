#include "pzhelp"
PROGRAM {
  int N, i, j;
  REAL t=0.0, perc;
  char a[100];
  N = READ_INT();
  SKIP_LINE();
for(i=0; i<N; i++){

  a[0] = getchar();
  if(a[0] == '\n') WRITELN("empty");

    else{//1
      j=1;
      while((a[j] = getchar()) !='\n') j=j+1;
      if(j>20) WRITELN("error");

        else{//2
          int x=0; int z;
          z=j-1;
          while((a[x] == a[z]) AND (x<=((j-1)/2)))
          {x=x+1; z=z-1;}
          if (x>((j-1)/2)) {WRITELN("yes"); t=t+1.0;}
            else WRITELN("no");
  }//else2
 }//else1
}//for
  perc = (t/N)*100*1.0;
  WRITELN(FORM(perc, 0, 3));
}//PROGRAM