#include <iostream>
using namespace std;

class list{
  public:
    list ();
    bool empty ();
    int  size ();
    void add (int k, int x);
    int  get (int k);
    void remove (int k);

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

bool list::empty(){
  return head == NULL;
}

int list::size(){
  int total=0;
  node *p;

  for(p = head; p != NULL; p=p->next)
    total++;

  return total;
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

int list::get(int k){

  node *p = head;
  for(int i=1; i<k; i++)
    p = p->next;
  return p->info;
}

void list::remove(int k){

  node *del = head;

  if(k==1 && head->next == NULL){
    head = NULL;
  }

  else if(k==1 && head->next != NULL){
    head = del->next;
    delete del;
  }

  else if(k>1){

    node *prev;

    for(int i=1; i<k; i++){
      prev = del;
      del = del->next;
    }

    prev->next=del->next;
    delete del;
  }
}

int main(){
  list catalogue;
  int N, M, k, x;

  scanf("%d", &N); //adding
  for(int i=0; i<N; i++){
    scanf("%d", &k);
    scanf("%d", &x);
    catalogue.add(k, x);
  }

  scanf("%d", &M); //removing
  for(int i=0; i<M; i++){
    scanf("%d", &k);
    catalogue.remove(k);
  }

  scanf("%d", &k);
  int Size = catalogue.size(); //size and data at the K box
  int data = catalogue.get(k);

  printf("%d", Size);
  printf(" ");
  printf("%d\n", data);
}