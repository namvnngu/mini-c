#include <stdio.h>

void fizzbuzz(char buf[], int bufsize, int upto) {
  int formatted_size = 0;

  for (int index = 1; index <= upto; index++) {
    if (index % 15 == 0) {
      formatted_size += snprintf(buf + formatted_size,
                                 bufsize - formatted_size,
                                 index == upto ? "%s." : "%s, ",
                                 "FizzBuzz");
    } else if (index % 3 == 0) {
      formatted_size += snprintf(buf + formatted_size,
                                 bufsize - formatted_size,
                                 index == upto ? "%s." : "%s, ",
                                 "Fizz");
    } else if (index % 5 == 0) {
      formatted_size += snprintf(buf + formatted_size,
                                 bufsize - formatted_size,
                                 index == upto ? "%s." : "%s, ",
                                 "Buzz");
    } else {
      formatted_size += snprintf(buf + formatted_size,
                                 bufsize - formatted_size,
                                 index == upto ? "%d." : "%d, ",
                                 index);
    }
  }
}

int main(void) {
  int BUFSIZE = 10000;
  char buf[BUFSIZE];
  fizzbuzz(buf, BUFSIZE, 100);
  printf("%s\n", buf);
}
