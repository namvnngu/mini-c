#include <stdio.h>

void fizzbuzz(char buf[], int bufsize, int upto) {
  int fmtsize = 0;

  for (int i = 1; i <= upto; i++) {
    char *str = buf + fmtsize;
    int restsize = bufsize - fmtsize;
    int islast = i == upto;

    if (i % 15 == 0) {
      fmtsize += snprintf(str, restsize, islast ? "%s." : "%s, ", "FizzBuzz");
    } else if (i % 3 == 0) {
      fmtsize += snprintf(str, restsize, islast ? "%s." : "%s, ", "Fizz");
    } else if (i % 5 == 0) {
      fmtsize += snprintf(str, restsize, islast ? "%s." : "%s, ", "Buzz");
    } else {
      fmtsize += snprintf(str, restsize, islast ? "%d." : "%d, ", i);
    }
  }
}

int main(void) {
  char buf[1000];
  fizzbuzz(buf, sizeof buf, 100);
  printf("%s\n", buf);
}
