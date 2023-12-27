#include <iostream>
#include <cstdio>
using namespace std;

int main(){
  int n, x, total=0;
  scanf("%d", &n);
  scanf("%d", &x);
  int a[n+1];
  bool control;

  for(int z=1; z<=n; z++)
    scanf("%d", &a[z]);

  for(int i=1; i<n; i++){
    control=true;
    if(a[i] >= x) control=false;
    if(control==true){
      for(int j=i+1; j<n+1; j++)
        if(a[i] + a[j] == x) total++;
    }
  }
  printf("%d\n", total);
  return 0;
}