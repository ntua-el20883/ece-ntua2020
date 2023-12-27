#include <iostream>
#include <cstdio>
using namespace std;

int main(){
  int N, p, i, j, z, t;
  t=1;
  scanf ("%d", &N);
  bool a[N+1];

  if((N==0) || (N==1)) printf("0\n");

  else {
    for(i=0; i<N; i++)   a[i] = false;
    a[N] = true;

    for (p=2; p<N; p++)
    {
      if (N%p == 0)
      {
        for (j=p; j<N; j+=p)
          a[j] = true;
      }
    }

    for(z=2; z<N; z++)
      if (a[z] == true) t+=1;

    printf("%d\n", t);
  }
  return 0;
}