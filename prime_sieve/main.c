#include <stdio.h>

int main(void) {
  const int MAX_NUMBER = 1000;
  const int FIRST_PRIME = 2;
  const int NUM_ELEMENTS = MAX_NUMBER - FIRST_PRIME + 1;
  int primes[NUM_ELEMENTS];

  for (int i = 0; i < NUM_ELEMENTS; i++) {
    if (i == 0) {
      primes[i] = FIRST_PRIME;
    } else {
      int current_number = FIRST_PRIME + i;
      primes[i] = current_number % 2 == 0 ? 0 : current_number;
    }
  }

  for (int i = 1; i < NUM_ELEMENTS; i++) {
    int smallest = primes[i];
    if (smallest == 0) {
      continue;
    }

    for (int j = i + 1; j < NUM_ELEMENTS; j++) {
      if (primes[j] % smallest == 0) {
        primes[j] = 0;
      }
    }
  }

  int prime_count = 0;
  for (int i = 0; i < NUM_ELEMENTS; i++) {
    if (primes[i] != 0) {
      prime_count++;
      printf("%d ", primes[i]);
    }
  }

  printf("\n\nThere are %d prime numbers up to the number %d.\n",
         prime_count,
         MAX_NUMBER);
}
