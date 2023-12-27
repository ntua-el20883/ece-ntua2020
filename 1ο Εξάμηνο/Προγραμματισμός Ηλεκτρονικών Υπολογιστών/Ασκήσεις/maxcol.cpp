#include <iostream>
#include <cstdio>
using namespace std;

int main(){
  int N, M;
  scanf("%d", &N);
  scanf("%d", &M);
  int A[N][M], sum[M], J=0, maxsum=0;

  for(int i=0; i<N; i++)
    for(int j=0; j<M; j++)
      scanf("%d", &A[i][j]);

  for(int j=0; j<M; j++){
    sum[j]= A[0][j];
    for(int i=1; i<N; i++){
      sum[j]+= A[i][j];
    }
    if(sum[j] >= maxsum){
      maxsum = sum[j];
      J=j;
    }
  }

  printf("%d", J+1);
  printf(" ");
  printf("%d\n", maxsum);
  return 0;
}