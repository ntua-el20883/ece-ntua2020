#include <iostream>
using namespace std;

struct node{
  int info;
  node *left, *right;
};

class bstree{
  public:
    bstree();
    int height();
    void insert(int x);
    int search(int x);
    int min();
    int max();
    void inorder();
    void preorder();
    void postorder();
  private:
    node *root;
};

int height_aux(node *t);  //declaring auxiliar functions
node *insert_aux(node *t, int x);
int search_aux(node *t, int x, int level);
void inorder_aux(node *t);
void preorder_aux(node *t);
void postorder_aux(node *t);

bstree::bstree(){  //normal functions
  root = NULL;
}

int bstree::height(){
  return height_aux(root);
}

void bstree::insert(int x){
  root = insert_aux(root, x);
}

int bstree::search(int x){
  int level=1;
  return search_aux(root, x, level);
}

int bstree::min(){
  int minimum;
  for(node *p=root; p != NULL; p=p->left)
    minimum = p->info;
  return minimum;
}

int bstree::max(){
  int maximum;
  for(node *p=root; p != NULL; p=p->right)
    maximum = p->info;
  return maximum;
}

void bstree::inorder(){
  inorder_aux(root);
}

void bstree::preorder(){
  preorder_aux(root);
}

void bstree::postorder(){
  postorder_aux(root);
}

int height_aux(node *t){  //auxiliar functions
  if(t == NULL) return 0;
  else
    return 1 + max(height_aux(t->left), height_aux(t->right));
}

node *insert_aux(node *t, int x){
  if(t == NULL){
    node *p = new node;
    p->info = x;
    p->left = NULL;  p->right = NULL;
    return p;
  }

  if(x < t->info)
    t-> left = insert_aux(t->left, x);
  else
    t->right = insert_aux(t->right, x);
  return t;
}

int search_aux(node *t, int x, int level){

  if(t == NULL) return 0;

  if(t->info == x) return level;

  if(t->info > x){
    level++;
    return search_aux(t->left, x, level);
  }
  else{
    level++;
    return search_aux(t->right, x, level);
  }
}

void inorder_aux(node *t){
  if(t != NULL){
    inorder_aux(t->left);
    printf("%d ", t->info);
    inorder_aux(t->right);
  }
}

void preorder_aux(node *t){
  if(t != NULL){
    printf("%d ", t->info);
    preorder_aux(t->left);
    preorder_aux(t->right);
  }
}

void postorder_aux(node *t){
  if(t != NULL){
    postorder_aux(t->left);
    postorder_aux(t->right);
    printf("%d ", t->info);
  }
}

int main(){
  bstree oak;
  int N, M, x;

  scanf("%d", &N);  //adding
  for(int i=0; i<N; i++){
    scanf("%d", &x);
    oak.insert(x);
  }

  int altitude = oak.height();
  printf("%d\n", altitude);

  int Small = oak.min(), Big = oak.max();
  printf("%d %d\n", Small, Big);

  scanf("%d", &M);
  for(int i=0; i<M; i++){
    scanf("%d", &x);
    int result = oak.search(x);
    if(i==0) printf("%d", result);
    else printf(" %d", result);
  }
  printf("\n");

  oak.inorder();
  printf("end\n");

  oak.preorder();
  printf("end\n");

  oak.postorder();
  printf("end\n");
}