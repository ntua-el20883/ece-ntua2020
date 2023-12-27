#include <iostream>
#include <cstdio>
using namespace std;

int main()
{
  int N;
  bool in=true;
  scanf("%d", &N);
  int a[N][N], sumr[N], sumc[N], sumD=0, sumd=0;

  //getting the magic box
  for(int i=0; i<N; i++)
    for(int j=0; j<N; j++)
    {
      scanf("%d", &a[i][j]);
      if(a[i][j] >((N*N)-1))
      {
        printf("no\n");
        in=false;
        break;
      }
      if(in==false) break;
    }

  if(in==true)
  {
    for(int i=1; i<N; i++)
    {
      for(int j=0; j<N; j++)
        if(a[i][j]==a[i][j+1])
        {
          printf("no\n");
          in=false;
          break;
        }
      if(in==false) break;
    }
  }

  //sum of rows
  if(in==true)
  {
    for(int i=0; i<N; i++)
    {
      sumr[i] = a[i][0];
      for(int j=1; j<N; j++)
        sumr[i] += a[i][j];
    }

    for(int i=0; i<N-1; i++)
      if(sumr[i] != sumr[i+1])
      {
        printf("no\n");
        in=false;
        break;
      }
  }

  //sum of columns
 if(in==true)
 {
   for(int j=0; j<N; j++)
   {
     sumc[j] = a[0][j];
     for(int i=1; i<N; i++)
       sumc[j] += a[i][j];
   }
   for(int j=0; j<N-1; j++)
     if(sumc[j] != sumc[j+1])
     {
       printf("no\n");
       in=false;
       break;
     }
 }

 //sum of Diagonal-diagonal
 if(in==true)
 {
   for(int i=0; i<N; i++)
   {
     for(int j=0; j<N; j++)
       if(i==j) sumD+= a[i][j];
   }

   for(int i=0; i<N; i++)
   {
     for(int j=N-1; j>=0; j--)
       if((i+j)==(N-1)) sumd+= a[i][j];
   }

   if(sumD!=sumd)
   {
     printf("no\n");
     in=false;
   }
 }

 if(in==true) printf("yes\n");
  return 0;
}

