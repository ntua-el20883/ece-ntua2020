#include <iostream>
#include <cstdio>
using namespace std;

int main(){
  bool in=true;
  char encrypted_alphabet[26];
  char line[10000], encrypted_line[10000];
  int c=0, x, balader[10000];

  //getting the encrypted alphabet
  for(int i=0; i<26; i++){             //0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25
    encrypted_alphabet[i]=getchar();  //a b c d e f g h i j  k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z
   if((encrypted_alphabet[i] < 97) || (encrypted_alphabet[i]>122)) {
      printf("error\n");
      in=false;
      break;
   }
  }

  if(in==true){
    for(int i=0; i<26; i++){
      for(int j=1; j<26; j++)
        if((encrypted_alphabet[i]==encrypted_alphabet[j]) && (i!=j)) {
          printf("error\n");
          in=false;
          break;
        }
      if(in==false) break;
    }
  }

  //getting the line-encrypting
  if(in==true){//if1

    while(getchar()!='\n');

    balader[0]=getchar();
    while(balader[c] != EOF){
      line[c]=balader[c];
      c++;
      balader[c]=getchar();
    }

    for(int i=0; i<c; i++){
      if((line[i] >= 97) && (line[i] <= 122)){
        x=line[i];
        encrypted_line[i]=encrypted_alphabet[x-97];
      }

      else if((line[i] >= 65) && (line[i] <= 90)){
        x=line[i];
        encrypted_line[i]= encrypted_alphabet[x-65] - 32;

      }
      else if(((line[i])<97) || (line[i]>122))
        encrypted_line[i]=line[i];
    }

    for(int i=0; i<c; i++)
      printf("%c", encrypted_line[i]);

  }//if1
  return 0;
}//main
