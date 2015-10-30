#include <stdlib.h>
#include <limits.h>

#include "arrays.h"

void fillRand3(int arr[],size_t sz){
  for(size_t i = 0; i<sz;i++)
    arr[i] = rand() % 2;
}

int checkRand3(int arr[],size_t sz){
  for(size_t i = 0; i<sz;i++)
    if(arr[i]!=0)
      if(arr[i]!=1)
	return 0;
  return 1;
}

int minValue(int arr[],size_t sz){
  int min = arr[0];
  for(size_t i = 0; i<sz;i++)
    if(arr[i]<min)
      min = arr[i];
  return min;
}

int minIndex(int arr[],size_t sz){
  int* min = &arr[0];
  for(size_t i = 0;i<sz;i++)
    if(arr[i]<*min)
      min = &arr[i];
  return min - arr;
}

int maxOccurance(int arr[],size_t sz){
  int elems = malloc(sizeof(int)*sz);
  int occurances = malloc(sizeof(int)*sz);
  int last_index = 1;

  elems[0] = arr[0];
  occurances[0] = 1;

  for(size_t i = 0; i < sz; i++)
    for(size_t j =0; j < sz;j++){
      if(j==last_index){
	elems[last_index] = arr[i];
	occurances[last_index] = 1;
	last_index++;
      }
    }
}

