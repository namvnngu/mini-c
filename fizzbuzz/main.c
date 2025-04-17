#include <stdio.h>

void fizzbuzz(char buf[], int buf_size, int up_to) {
  int total_written_size = 0;

  for (int i = 1; i <= up_to; i++) {
    int remaining_size = buf_size - total_written_size;

    if (remaining_size <= 0) {
      break;
    }

    char *curr_pos = buf + total_written_size;
    int is_last = (i == up_to);
    int written_size = 0;
    const char *suffix = is_last ? "." : ", ";

    if (i % 15 == 0) {
      written_size = snprintf(curr_pos, remaining_size, "FizzBuzz%s", suffix);
    } else if (i % 3 == 0) {
      written_size = snprintf(curr_pos, remaining_size, "Fizz%s", suffix);
    } else if (i % 5 == 0) {
      written_size = snprintf(curr_pos, remaining_size, "Buzz%s", suffix);
    } else {
      written_size = snprintf(curr_pos, remaining_size, "%d%s", i, suffix);
    }

    if (written_size < 0 || written_size >= remaining_size) {
      break;
    }

    total_written_size += written_size;
  }
}

int main(void) {
  char buf[1000];
  fizzbuzz(buf, sizeof(buf), 100);
  printf("%s\n", buf);
}
