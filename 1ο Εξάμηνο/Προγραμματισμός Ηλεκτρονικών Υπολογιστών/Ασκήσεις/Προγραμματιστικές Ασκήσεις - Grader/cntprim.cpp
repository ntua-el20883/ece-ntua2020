#include <iostream>
using namespace std;

int main() {

  int N, p, i, j, z, t;
  t=0;
  scanf ("%d", &N);
  bool prime[N+1];

  for(z=2; z<=N; z++)   prime[z] = true;

  for (p=2; (p*p)<=N; p++)
    {
      if (prime[p] == true)
      {
        for (i=(p*p); i<=N; i+=p)
          prime[i] = false;
      }
    }

      for(j=2; j<=N; j++)   if (prime[j] == true) t+=1;

    printf("%d\n", t);
  return 0;
}