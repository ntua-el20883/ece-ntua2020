#include <iostream>
#include <cmath>
using namespace std;

void sumofpow(int N){
  int pow_two[23], pow_three[15], pow_five[10], total=0;
  bool count[N+1];

  for(int i=0; i<=N; i++)
    count[i] = false;

  for(int i=0; i<23; i++)
    pow_two[i] = pow(2, i);

  for(int i=0; i<15; i++)
    pow_three[i] = pow(3, i);

  for(int i=0; i<10; i++)
    pow_five[i] = pow(5, i);

  for(int i=0; i<23; i++){//for1

    if(pow_two[i] >= N) break;

    for(int j=0; j<15; j++){//for2

      if(pow_three[j] >= N) break;
      else if(pow_two[i] + pow_three[j] >= N) break;

      for(int z=0; z<10; z++){//for3

        int sum = pow_two[i] + pow_three[j] + pow_five[z];

        if(pow_five[z] >= N) break;
        else if(sum > N) break;
        else if(sum <= N) count[sum] = true;
      }//for3
    }//for2
  }//for1

  for(int i=0; i<=N; i++)
    if(count[i]==true) total++;
  printf("%d\n", total);

}//void

int main(){
  int N;
  scanf("%d", &N);

  sumofpow(N);
  return 0;
}