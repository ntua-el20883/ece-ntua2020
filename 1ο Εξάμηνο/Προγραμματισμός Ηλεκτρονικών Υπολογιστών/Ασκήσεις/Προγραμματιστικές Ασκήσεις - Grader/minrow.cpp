#include <iostream>
#include <cstdio>
using namespace std;

int main(){
  int N, M;
  scanf("%d", &N);
  scanf("%d", &M);
  int A[N][M], least_sum=9999999, row_sum[N], I;

  for(int i=0; i<N; i++)
    for(int j=0; j<M; j++)
      scanf("%d", &A[i][j]);

  for(int i=0; i<N; i++){
    row_sum[i]=A[i][0];
    for(int j=1; j<M; j++){
      row_sum[i]+=A[i][j];
      if(row_sum[i] > least_sum) break;
    }

    if(row_sum[i] <= least_sum){
      least_sum=row_sum[i];
      I=i;
    }
  }

  printf("%d", I+1);
  printf(" ");
  printf("%d\n", least_sum);
  return 0;
}