#include <iostream>
using namespace std;

class list{
  public:
    list ();
    void add (int k, int x);
    int searchMF (int x);

  private:
    struct node {
      int info;
      node *next;
    };
    node *head;
};

list::list(){
  head = NULL;
}

void list::add(int k, int x){

  node *t = new node;
  t->info = x;

  if(k==1){
    t->next=head;
    head=t;
  }
  else if(k>1){

    node *post = head, *prev;

    for(int i=1; i<k; i++){
      prev = post;
      post=post->next;
    }

    prev->next=t;
    t->next=post;
  }
}

int list::searchMF(int x){
  int place=0, k=1;
  node *prev, *post=head;

  if(post->info == x)
    place = 1;

  else{
    while(post->next != NULL){
      k++;
      prev = post;
      post = post->next;

      if(post->info == x) {
        place = k;
        break;
      }
    }
  }

  if(place > 1){
    node *t = new node;
    t->info = x;
    t->next = head;
    head = t;

    prev->next = post->next;
    delete post;
  }
return place;
}

int main(){
  list catalogue;
  int N, M, k, x, sum=0;

  scanf("%d", &N);  //adding
  for(int i=0; i<N; i++){
    scanf("%d", &k);
    scanf("%d", &x);
    catalogue.add(k, x);
  }

  scanf("%d", &M); //searchingMF (mothef-)
  for(int i=0; i<M; i++){
    scanf("%d", &x);
    sum+=catalogue.searchMF(x);
  }

  printf("%d\n", sum);
}


