#include <stdio.h>

int main(void) {
  const int UPTO = 1000;
  const int FIRST_PRIME = 2;
  const int N = UPTO - FIRST_PRIME + 1;
  int list[UPTO];

  for (int i = 0; i < N; i++) {
    if (i == 0) {
      list[i] = FIRST_PRIME;
    } else {
      int num = FIRST_PRIME + i;
      list[i] = num % 2 == 0 ? 0 : num;
    }
  }

  for (int smallest_i = 1; smallest_i < N; smallest_i++) {
    int smallest = list[smallest_i];
    if (smallest == 0) {
      continue;
    }

    for (int i = smallest_i + 1; i < N; i++) {
      if (list[i] % smallest == 0) {
        list[i] = 0;
      }
    }
  }

  int count = 0;
  for (int i = 0; i < N; i++) {
    if (list[i] != 0) {
      count++;
      printf("%d ", list[i]);
    }
  }
  printf("\n\nThere are %d prime numbers up to the number %d.\n", count, UPTO);
}
