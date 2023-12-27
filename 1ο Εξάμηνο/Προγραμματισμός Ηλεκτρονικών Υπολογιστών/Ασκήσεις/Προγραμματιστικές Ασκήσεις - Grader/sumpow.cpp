    #include <iostream>  
    #include <cstdio>  
    #include <cmath>  
    using namespace std;  
      
    int main(){  
      int N, number, last_digit, sum,  p[10];  
      scanf("%d", &N);  
        
      for(int i=0; i<10; i++)  
        p[i] = pow(i, N);  
      
       printf("0\n");  
       printf("1\n");  
      for(int i=2; i<100000000; i++){  
        number=i;  
        sum=0;  
        while(number>0){  
          last_digit=number%10;  
          sum+=p[last_digit];  
          number/=10;  
        }  
        if(sum==i) printf("%d\n", sum);  
      }  
      return 0;  
    }  