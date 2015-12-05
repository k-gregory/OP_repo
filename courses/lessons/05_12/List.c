#include <stdlib.h>
#include <stdio.h>

typedef struct _LinkedList LinkedList;

struct _LinkedList {
  int val;
  LinkedList *next;
};

void ll_add(LinkedList *after, int val) {
  LinkedList *new_el = malloc(sizeof(LinkedList));
  new_el->val = val;
  new_el->next = after->next;
  after->next = new_el;
}

void ll_remove(LinkedList *after) {
  LinkedList *next = after->next->next;
  free(after->next);
  after->next = next;
}

void ll_insert(LinkedList *root, int val, size_t index) {
  for(size_t i = 0; i<index;i++)
    root = root->next;
  ll_add(root,val);
}

LinkedList* ll_reverse(LinkedList* root){
  LinkedList* new_root = NULL;
  while(root!=NULL){
    LinkedList* next = root->next;
    root->next = new_root;
    new_root = root;
    root = next;
  }
  return new_root;
}

LinkedList* ll_new(int val){
  LinkedList* ret =  malloc(sizeof(LinkedList));
  ret->val = val;
  ret->next = NULL;
  return ret;
}

void ll_free(LinkedList *root) {
  while (root != NULL) {
    LinkedList *r = root->next;
    free(root);
    root = r;
  }
}

void ll_print(LinkedList* root){
  while(root!=NULL){
    printf("%d->",root->val);
    root = root->next;
  }
  puts("NULL");
}

int main(void) {
  LinkedList* list = ll_new(0);
  for(size_t i =1;i<=5;i++)
    ll_insert(list,i,i-1);
  ll_print(list);
  
  list = ll_reverse(list);
  ll_print(list);

  ll_free(list);
  return EXIT_SUCCESS;
}
