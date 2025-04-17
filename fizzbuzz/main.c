#include <stdio.h>

void fizzbuzz(char buf[], int buf_size, int up_to) {
  int total_written = 0;

  for (int i = 1; i <= up_to; i++) {
    int remaining_size = buf_size - total_written;

    if (remaining_size <= 0) {
      break;
    }

    char *current_pos = buf + total_written;
    int is_last = (i == up_to);
    int written = 0;
    const char *suffix = is_last ? "." : ", ";

    if (i % 15 == 0) {
      written = snprintf(current_pos, remaining_size, "FizzBuzz%s", suffix);
    } else if (i % 3 == 0) {
      written = snprintf(current_pos, remaining_size, "Fizz%s", suffix);
    } else if (i % 5 == 0) {
      written = snprintf(current_pos, remaining_size, "Buzz%s", suffix);
    } else {
      written = snprintf(current_pos, remaining_size, "%d%s", i, suffix);
    }

    if (written < 0 || written >= remaining_size) {
      break;
    }

    total_written += written;
  }
}

int main(void) {
  char buf[1000];
  fizzbuzz(buf, sizeof(buf), 100);
  printf("%s\n", buf);
}
