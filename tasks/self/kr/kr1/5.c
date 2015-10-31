#include <stdio.h>

#define LEN 10

void sub(int arr1[], int arr2[],int res_arr[], size_t sz){
  for(size_t i = 0; i< sz; i++)
    res_arr[i]=arr1[i]-arr2[i];
}

int min(int arr[], size_t sz){
  int m = arr[0];
  for(size_t i =0;i<sz;i++)
    if(arr[i]<m)
      m = arr[i];
  return m;
}

int main(void){
  int arr1[LEN] = {1,2,3,4,5,6,7,8,9,3};
  int arr2[LEN] = {23,5,6,2,86,23,23,5,1,4};
  int res[LEN]; 
  sub(arr1,arr2,res,LEN);

  for(int i =0 ;i<LEN;i++)
    printf("%d ",arr1[i]);
  
  for(int i =0 ;i<LEN;i++)
    printf("%d ",arr2[i]);

  for(int i = 0;i<LEN;i++)
    printf("%d ",res[i]);

  printf("Min diff: %d\n",min(res,LEN));
  return 0;
}
