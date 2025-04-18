#include <stdio.h>
#include <string.h>

char *ones[] = {
  "",        "one",     "two",       "three",    "four",
  "five",    "six",     "seven",     "eight",    "nine",
  "ten",     "eleven",  "twelve",    "thirteen", "fourteen",
  "fifteen", "sixteen", "seventeen", "eighteen", "nineteen",
};

char *tens[] = {
  // clang-format off
  "",      "",      "twenty",  "thirty", "forty",
  "fifty", "sixty", "seventy", "eighty", "ninety",
  // clang-format on
};

struct testcase_t {
  char *number;
  char *expected;
};

void format_hundred(int num) {
  if (num >= 1000) {
    fprintf(
      stderr,
      "\033[31mformat_hundred(%d) failed: The given number must be below 1000.\033[0m\n",
      num);
    return;
  }

  if (num >= 100) {
    printf("%s hundred", ones[num / 100]);
    num %= 100;
  }
  if (num >= 20) {
    printf("%s ", tens[num / 10]);
    num %= 10;
  }
  if (num > 0) {
    printf("%s ", ones[num / 10]);
  }
}

void number_wordinator(char *words, int words_size, char *number) {
}

int main(void) {
  format_hundred(1000);
  struct testcase_t testcases[] = {
    {
      .number = "0",
      .expected = "zero",
    },
    {
      .number = "000",
      .expected = "zero",
    },
    {
      .number = "7",
      .expected = "seven",
    },
    {
      .number = "19",
      .expected = "nineteen",
    },
    {
      .number = "019",
      .expected = "nineteen",
    },
    {
      .number = "20",
      .expected = "twenty",
    },
    {
      .number = "21",
      .expected = "twenty-one",
    },
    {
      .number = "99",
      .expected = "ninety-nine",
    },
    {
      .number = "100",
      .expected = "one hundred",
    },
    {
      .number = "00100",
      .expected = "one hundred",
    },
    {
      .number = "101",
      .expected = "one hundred and one",
    },
    {
      .number = "110",
      .expected = "one hundred and ten",
    },
    {
      .number = "112",
      .expected = "one hundred and twelve",
    },
    {
      .number = "120",
      .expected = "one hundred and twenty",
    },
    {
      .number = "143",
      .expected = "one hundred and forty-three",
    },
    {
      .number = "999",
      .expected = "nine hundred and ninety-nine",
    },
    {
      .number = "1000",
      .expected = "one thousand",
    },
    {
      .number = "00001000",
      .expected = "one thousand",
    },
    {
      .number = "1001",
      .expected = "one thousand and one",
    },
    {
      .number = "1010",
      .expected = "one thousand and ten",
    },
    {
      .number = "1043",
      .expected = "one thousand and forty-three",
    },
    {
      .number = "0000001043",
      .expected = "one thousand and forty-three",
    },
    {
      .number = "1100",
      .expected = "one thousand, one hundred",
    },
    {
      .number = "1101",
      .expected = "one thousand, one hundred and one",
    },
    {
      .number = "1143",
      .expected = "one thousand, one hundred and forty-three",
    },
    {
      .number = "9999",
      .expected = "nine thousand, nine hundred and ninety-nine",
    },
    {
      .number = "1000000",
      .expected = "one million",
    },
    {
      .number = "00001000000",
      .expected = "one million",
    },
    {
      .number = "1000001",
      .expected = "one million and one",
    },
    {
      .number = "1000100",
      .expected = "one million, one hundred",
    },
    {
      .number = "1001100",
      .expected = "one million, one thousand, one hundred",
    },
    {
      .number = "1147483647",
      .expected =
        "one billion, one hundred and forty-seven million, four hundred and "
        "eighty-three thousand, six hundred and forty-seven",
    },
    {
      .number = "0001147483647",
      .expected =
        "one billion, one hundred and forty-seven million, four hundred and "
        "eighty-three thousand, six hundred and forty-seven",
    },
    {
      .number = "123456789",
      .expected = "one hundred and twenty-three million, four hundred and "
                  "fifty-six thousand, seven hundred and eighty-nine",
    },
    {
      .number = "2000000000",
      .expected = "two billion",
    },
    {
      .number = "000002000000000",
      .expected = "two billion",
    },
    {
      .number = "7828660194658220598",
      .expected =
        "seven quintillion, eight hundred and twenty-eight quadrillion, six "
        "hundred and sixty trillion, one hundred and ninety-four billion, six "
        "hundred and fifty-eight million, two hundred and twenty thousand, "
        "five hundred and ninety-eight",
    },
    {
      .number = "0007828660194658220598",
      .expected =
        "seven quintillion, eight hundred and twenty-eight quadrillion, six "
        "hundred and sixty trillion, one hundred and ninety-four billion, six "
        "hundred and fifty-eight million, two hundred and twenty thousand, "
        "five hundred and ninety-eight",
    },
  };

  int passed = 0;
  int total = sizeof(testcases) / sizeof(struct testcase_t);

  for (int i = 0; i < total; i++) {
    struct testcase_t testcase = testcases[i];
    char *number = testcase.number;
    char *expected = testcase.expected;
    char words[1000] = {0};
    int words_size = sizeof(words);

    number_wordinator(words, words_size, number);

    if (strcmp(words, expected) == 0) {
      passed++;
      printf("\033[1;42m PASS \033[0m \033[1m%s\033[0m\n", number);
    } else {
      printf("\033[1;41m FAIL \033[0m \033[1m%s\033[0m\n", number);
      printf("  \033[32mExpected\033[0m: %s\n", expected);
      printf("    \033[31mActual\033[0m: %s\n", words);
    }
  }

  int failed = total - passed;

  printf("\n\033[1;43m   REPORT   \033[0m\n");
  printf("Total:  \033[1m%d\033[0m\n", total);
  if (passed != 0) {
    printf("Passed: \033[1;32m%d\033[0m\n", passed);
  }
  if (failed != 0) {
    printf("Failed: \033[1;31m%d\033[0m\n", failed);
  }
}
