#include <iostream>
#include <cstdio>
using namespace std;
void format(char a[], int words, int last_space){

  int x=1, spaces_per_word, spaces_per_line, spaces_to_add, extra_spaces, words_with_no_extra_spaces;
  char c[1000];

  if(a[60] == ' ') spaces_to_add = 1;

  if((a[60] != ' ') && (a[61] == ' ')) spaces_to_add = 0;

  if((a[60] != ' ') && (a[61] != ' ')) spaces_to_add = 60 - last_space + 1; //+1 for the last_space

  spaces_per_line = words - 1;

  spaces_per_word = spaces_to_add / spaces_per_line;

  extra_spaces = spaces_to_add % spaces_per_line;

  words_with_no_extra_spaces = words - extra_spaces;

  for(int y=1; y<last_space; y++){

    if(a[y] != ' ') c[x++] = a[y];

    if(a[y] == ' '){

      c[x++] = ' ';

      words_with_no_extra_spaces--;
      if(spaces_per_word > 0)
        for(int z = spaces_per_word; z>0; z--)
          c[x++] = ' ';

      if(words_with_no_extra_spaces <= 0)
        c[x++] = ' ';
    }
  }
  for(int y=1; y<61; y++)
    printf("%c", c[y]);
  cout << endl;
}

int main(){
  char a[1000], b[1000];
  int c, i=1, words=0, last_space;

   a[1] = getchar();

   while(a[1] == ' ')
      a[1] = getchar();

   c = getchar();

   while(true){

    last_space=1;  words=0;

    while(i < 61){

      if(c == EOF) break;

      if(c == '\n') c = ' ';

      if(a[i] != ' ')
        a[++i] = c;

      if(a[i] == ' ' && (c != ' ')){
          a[++i] = c;
          words++;
          if(i > last_space) last_space=i-1;
      }
      c = getchar();
    }

    if(c == EOF){
      for (int j=1; j<=i-1; j++)
        printf ("%c", a[j]);
      cout << endl;
      break;
    }

    if (a[61]== ' '){
      for (int j=1; j<=i-1; j++)
        printf ("%c", a[j]);
      cout << endl;
      i=1;
      a[1] = c;
      while(a[1] == ' ' || a[1] == '\n')
        a[1] = getchar();
 c = getchar();
      continue;
    }

    for(int j=last_space+1; j<=61; j++)
      b[j] = a[j];

    format(a, words, last_space);

   if(a[61] != ' '){
     i=0;
     for(int z=last_space+1; z<=61; z++)
       a[++i] = b[z];
   }

   if(a[61] == ' ') i=0;
  }
}