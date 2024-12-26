#include <stdlib.h>
#include <stdio.h>

void initialize_array(int *arr, size_t length) {
  for (size_t i = 0; i < length; ++i) {
    for (size_t j = 0; j < 3; ++j)
    {
      *(arr + (i * 3) + j) = 3;
    }
    
  }
}

// [1,1,1],[1,1,1],[1,1,1]

typedef struct S {
  int *field;
} S;

int main() {
  printf("\n\nRunning program\n\n");
  int arr[3][3];
  initialize_array(&arr[0][0], 3);
  for (size_t i = 0; i < 3; i++)
  {
    for (size_t j = 0; j < 3; ++j)
    {
      printf("%d", arr[i][j]);
    }
    
  }
  printf("\n");

  int x = 3;
  int y = 6;
  S s = {.field=&x};
  S s2 = s;

  *s2.field = 9; // de referencing the pointer member of s2 and reassigning it also reassigns it for s

  printf("%i %i\n", *s.field, *s2.field);
  
  return 0;
}