#include <stdlib.h>
#include <stdio.h>

typedef struct _LinkedList LinkedList;

struct _LinkedList{
  int val;
  LinkedList* next;
  LinkedList* first;
};

void ll_add(LinkedList* to, int val){
  LinkedList* new_el = malloc(sizeof(LinkedList));
  new_el->val = val;
  new_el->next = to->next;
  new_el->first = to->first;
  to->next = new_el;
}

void ll_insert(LinkedList* root, int val, size_t index){
  if(index == 0){
    LinkedList* new_root = malloc(sizeof(LinkedList));
    new_root->val = val;
    new_root->next = root;
    new_root->first = new_root;
  }
  root = root->first;
  for(size_t i = 0;i<index-1;i++)
      root = root->next;
  ll_add(root, val);
}

void ll_remove(LinkedList* root, size_t index){
  root = root->first;
  size_t i;
  for(i = 0; i<index-1;i++)
    root = root->next;
  LinkedList* next = root->next->next;
  free(root->next);
  root->next = next;
}

size_t ll_count(LinkedList* root){
  root = root->first;
  size_t count = 1;
  while((root=root->next)!=0)
    count++;
  return count;
}

inline LinkedList* ll_first(LinkedList* root){
  return root->first;
}

inline LinkedList* ll_last(LinkedList* root){
  while(root->next!=NULL)
    root = root->next;
  return root;
}

int ll_element_at(LinkedList* root, size_t index){
  root=  root->first;
  for(size_t i = 0;i<index;i++)
    root = root->next;
  return root->val;
}

size_t ll_index_of(LinkedList* root, int val){
  size_t index = 0;
  while(root!=NULL){
    if(root->val==val)
      return index;
    index++;
    root = root->next;
  }
  return 0;
}

LinkedList* ll_reverse(LinkedList* root){
  LinkedList* new = root;
  while(root!=NULL){
    LinkedList* t = new;
    new = root;
    new->next = t;
    root=root->next;
  }
  new->first = new;
  return new;
}

int main(void){
  LinkedList list = {15,NULL,NULL};
  list.first = &list;
  ll_insert(&list, 145, 1);
  ll_insert(&list, 1, 1);
  ll_remove(&list, 1);
  printf("%d\n",ll_count(&list));
  printf("%d\n",ll_element_at(&list,0));
  printf("%d\n",ll_element_at(&list,1));
  printf("%d\n",ll_index_of(&list,145));
  LinkedList* rev_list = ll_reverse(&list);
  printf("%d\n",rev_list->next->val);
  return EXIT_SUCCESS;
}
