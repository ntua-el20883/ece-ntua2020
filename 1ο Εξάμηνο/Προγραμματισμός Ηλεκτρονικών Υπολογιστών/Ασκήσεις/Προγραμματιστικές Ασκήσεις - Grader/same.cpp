#include <iostream>
#include <cstdio>
using namespace std;

void swaping(int &x, int &y){
  int save;
  save = x;
  x = y;
  y = save;
}

int partitioning(int A[], int first, int last){

  int x = A[(first + last)/2];
  int i = first, j=last;

  while(true){
    while (A[i] < x) i++;
    while (x < A[j]) j--;
    if (i >= j) break;
    swaping(A[i], A[j]);
    i++;
    j--;
  }
  return j;
}

void quicksort(int A[], int first, int last){

  if(first >= last) return;

  int i = partitioning(A, first, last);
  quicksort(A, first, i);
  quicksort(A, i+1, last);
}

int main(){
  int N, c;
  scanf("%d", &N);
  int A[N], B[N];
  bool output=true, balader=true;

  for(int i=0; i<N; i++)
    scanf("%d", &A[i]);

  for(int i=0; i<N; i++)
    scanf("%d", &B[i]);
  quicksort(A, 0, N-1);
  quicksort(B, 0, N-1);

  for(c=0; c<N; c++){
    if(A[c] != B[c]){
      output = false;
      break;
    }
  }

  if(output==true) printf("yes\n");

  else if(output==false){

    printf("no ");

    if(A[c] > B[c]) printf("%d", B[c]);
    else if(A[c] < B[c]) printf("%d", A[c]);
    printf(" ");

    for(int i=N-1; i>=0; i--){
      for(int j=i; j>=0; j--){

        if(A[i] == B[j]) break;

        if(A[i] > B[j]){
          printf("%d\n", A[j]);
          balader=false;
          break;
          }

        else if(A[i] < B[j]){
          printf("%d\n", B[j]);
          balader=false;
          break;
        }
      }
      if(balader==false)break;
    }
  }
  return 0;
}
