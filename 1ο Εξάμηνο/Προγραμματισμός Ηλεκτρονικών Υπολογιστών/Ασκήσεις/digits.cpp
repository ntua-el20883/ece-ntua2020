#include <pzhelp>
#include <iostream>
using namespace std;

int main(){
  int K, N, B, L;
  int a[10000];
  int i, j, d;
  cin >> K;   i=0;

  for(j=0; j<K; j++){
    cin >> N;
    cin >> B;
    cin >> L;
   if (N==0) cout << "0" << endl;
   else {
     while (N > 0) {
       a[i] = N % B;
       N /= B;
       i++;
    }
    d=a[i-L];
    cout << d << endl;
  }//else
}//for

  return 0;
}