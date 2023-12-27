#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

int main(){
  int T, N, count, a[1001], w, sum;
  double root;
  scanf("%d", &T);

  for(int i=0; i<1001; i++)
    a[i] = i*i*i;

  for(int i=0; i<T; i++){
     scanf("%d", &N);
     count=0;

     for(int j=0; j<1001; j++){
       if(a[j] > N) break;

       for(int z=j; z<1001; z++){
           if(a[j] + 2*a[z] > N) break;

           sum = N - a[j] - a[z];

           root = cbrt(sum);

           root = round(root);

           w = (int) root;


           if( w >= z && a[j] + a[z] + a[w] == N)
             count++;
       }
     }
     printf("%d\n", count);
  }
  return 0;
}