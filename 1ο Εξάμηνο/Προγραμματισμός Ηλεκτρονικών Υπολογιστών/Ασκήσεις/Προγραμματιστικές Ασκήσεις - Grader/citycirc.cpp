#include <iostream>
#include <cstdio>
using namespace std;

int main(){
  int N, k=0, balader, money=0;
  scanf("%d", &N);
  int b[N+1];

  for(int i=1; i<=N; i++){
    scanf("%d", &b[i]);
    money+=b[i];
  }

  if(money<0) printf("0\n");

  else{
    while(k<=N){
      k++;
      money=b[k];
      balader=k+1;
      if(k==N) balader=1;

      while((money>=0) && (balader != k)){
        if(balader==N+1) balader=1;
        money+=b[balader];
        balader++;
      }

      if(k<=N && money>=0){
        printf("%d\n", k);
        break;
      }
    }

    if(k>N) printf("0\n");
  }
  return 0;
}