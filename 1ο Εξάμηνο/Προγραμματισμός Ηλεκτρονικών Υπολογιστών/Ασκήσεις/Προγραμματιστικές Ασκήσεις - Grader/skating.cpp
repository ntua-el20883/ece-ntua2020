#include <iostream>
using namespace std;

void skating(int road[], int N){
  int velocity=0, max_velocity=0;

  for(int i=N-1; i>=0; i--){
    velocity+=road[i];
    if(max_velocity < velocity) max_velocity = velocity;
  }
  printf("%d\n", max_velocity);
}

int main(){
  int N;
  scanf("%d", &N);
  int road[N];

  for(int i=0; i<N; i++)
    scanf("%d", &road[i]);

  skating(road, N);
  return 0;
}