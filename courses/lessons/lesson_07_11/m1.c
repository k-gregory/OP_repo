#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define LEN(arr) (sizeof(arr)/sizeof((arr)[0]))

static inline unsigned int m_idx(unsigned int row, unsigned int col, unsigned int row_length) {
  return (row - 1) * row_length + col -1;
}

void fillRand(int *arr, size_t length) {
  for (size_t i = 0; i < length; i++)
    arr[i] = rand()%100;
}

void printArr(int *arr, size_t length) {
  for (size_t i = 0; i < length - 1; i++)
    printf("%d ", arr[i]);
  printf("%d\n", arr[length - 1]);
}

void printMat(int* arr, size_t rows, size_t columns){
  for(size_t i=1;i<=rows;i++){
    for(size_t j=1;j<columns;j++)
      printf("%d\t",arr[m_idx(i,j,columns)]);
    printf("%d\n", arr[m_idx(i,columns,columns)]);
  }
}

int main(void) {
  char buff[50];
  int* arr;
  size_t n,m;
  printf("Please,enter matrix dismension(ex. '3 5')\n");
  fgets(buff,LEN(buff),stdin);
  while(sscanf(buff,"%zu %zu\n",&m,&n)!=2);
  arr = malloc(m*n*sizeof(int));

  srand(time(NULL));

  fillRand(arr, m * n);
  printMat(arr, m, n);

  free(arr);
  return EXIT_SUCCESS;
}
