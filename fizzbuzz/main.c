#include <stdio.h>

void fizzbuzz(char buf[], int bufsize, int upto) {
  int fmtsize = 0;

  for (int idx = 1; idx <= upto; idx++) {
    char *str = buf + fmtsize;
    int restsize = bufsize - fmtsize;
    int islast = idx == upto;

    if (idx % 15 == 0) {
      fmtsize += snprintf(str, restsize, islast ? "%s." : "%s, ", "FizzBuzz");
    } else if (idx % 3 == 0) {
      fmtsize += snprintf(str, restsize, islast ? "%s." : "%s, ", "Fizz");
    } else if (idx % 5 == 0) {
      fmtsize += snprintf(str, restsize, islast ? "%s." : "%s, ", "Buzz");
    } else {
      fmtsize += snprintf(str, restsize, islast ? "%d." : "%d, ", idx);
    }
  }
}

int main(void) {
  char buf[1000];
  fizzbuzz(buf, sizeof buf, 100);
  printf("%s\n", buf);
}
