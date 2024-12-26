#include <stdlib.h>
#include <stdio.h>

void initialize_array(int arr[], size_t length) {
  for (size_t i = 0; i < length; ++i) {
    arr[i] = 10;
  }
}

int main() {
  printf("\n\nRunning program\n\n");
  int arr[30];
  initialize_array(arr, 30);
  for (size_t i = 0; i < 30; i++)
  {
    printf("%i", arr[i]);
  }
  printf("\n");
  
  return 0;
}