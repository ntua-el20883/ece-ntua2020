#include <iostream>
#include <cstdio>
using namespace std;

int main(){
  int N;
  scanf("%d", &N);
  int a[N], x, j;
  bool b[N];

  for(int i=0; i<N; i++)
    scanf("%d", &a[i]);

  for(int i=0; i<N; i++){
    j=i;
    while(j>=0){
      if((a[j] % a[i]) != 0) { b[i]=false; break; }
      if((a[j] % a[i]) == 0) b[i]=true;
      j--;
    }
  }

  x=1000000000;
  for(int i=0; i<N; i++)
    if((b[i]==true) && (x > a[i])) x=a[i];

  printf("%d\n", x);
  return 0;
}