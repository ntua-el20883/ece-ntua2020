#include <iostream>
using namespace std;

class queue{
  public:
    queue ();
    bool empty ();
    void enqueue (int x);
    int  dequeue ();
    int  peek ();

  private:
    struct node{
      int info;
      node *next;
    };
    node *front, *rear;
};

queue::queue(){
  front = NULL;  rear = NULL;
}

bool queue::empty(){
  return front == NULL;
}

void queue::enqueue(int x){
  node *p = new node;
  p->info = x;
  p->next = NULL;
  if(front == NULL)
    front  = p;
  else
    rear->next = p;
  rear = p;
}

int queue::dequeue(){
  node *p = front;
  int result = front->info;
  if(front == rear)
    rear = NULL;
  front = front->next;
  delete p;
  return result;
}

int queue::peek(){
  int x;
  x = front->info;
  return x;
}

int main(){
  queue positive;
  queue negative;
  int number, pos=0, neg=0;
  bool control = true;

  while(scanf("%d", &number) != EOF){

    if(number > 0){
      pos++;   positive.enqueue(number);
    }

    else if(number < 0){
      neg++;   negative.enqueue(number);
    }
  }

  if(pos != neg) control = false;
  
  if(pos == neg){
    int P, N;

    while(true){
      P = positive.dequeue();
      N = negative.dequeue();
      N *= (-1);

      pos--;

      if(P != N){
        control = false;
        break;
      }

      if(pos == 0) break;
    }
  }

  if(control == false) printf("no\n");
  if(control == true) printf("yes\n");
}