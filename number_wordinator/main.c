#include <stdbool.h>
#include <stdio.h>
#include <string.h>

char *ones[] = {
  "zero",    "one",     "two",       "three",    "four",
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

char *groups[] = {
  // clang-format off
  "",         "thousand",    "million", "billion",
  "trillion", "quadrillion", "quintillion",
  // clang-format on
};

const size_t MAX_GROUP_LEN = 3;

struct testcase_t {
  char *input;
  char *expected;
};

void number_wordinator(char output[], size_t output_size, char input_digits[]) {
  size_t input_len = strlen(input_digits);

  bool evenly_divisible = input_len % MAX_GROUP_LEN == 0;
  size_t group_total = evenly_divisible ? input_len / MAX_GROUP_LEN
                                        : input_len / MAX_GROUP_LEN + 1;

  bool leading_zeros = true;
  size_t leading_zeros_group_count = 0;
  size_t output_len = 0;

  for (size_t group_i = 0; group_i < group_total; group_i++) {
    char group_digits[3] = {'0', '0', '0'};
    int char_offset_i = 0;
    if (evenly_divisible) {
      char_offset_i = group_i * MAX_GROUP_LEN;
    } else {
      int remainder = input_len % MAX_GROUP_LEN;
      int missing = MAX_GROUP_LEN - remainder;
      char_offset_i = MAX_GROUP_LEN * group_i - missing;
    }
    for (int i = 0; i < MAX_GROUP_LEN; ++i) {
      int digit_i = char_offset_i + i;
      if (digit_i >= 0 && digit_i < input_len) {
        group_digits[i] = input_digits[digit_i];
      }
    }

    int number = (group_digits[0] - '0') * 100  //
                 + (group_digits[1] - '0') * 10 //
                 + (group_digits[2] - '0');

    if (number != 0) {
      leading_zeros = false;
    }
    if (leading_zeros) {
      leading_zeros_group_count++;
      continue;
    }

    if (number >= 100) {
      char *format = number % 100 == 0 ? "%s hundred" : "%s hundred and ";
      output_len += snprintf(output + output_len,
                             output_size - output_len,
                             format,
                             ones[number / 100]);
      number %= 100;
    }
    if (number >= 20) {
      char *format = number % 10 == 0 ? "%s" : "%s-";
      output_len += snprintf(output + output_len,
                             output_size - output_len,
                             format,
                             tens[number / 10]);

      number %= 10;
    }
    if (number > 0) {
      char *format = "%s";
      output_len += snprintf(output + output_len,
                             output_size - output_len,
                             format,
                             ones[number]);
    }

    if (group_i != group_total - 1) {
      char *format = " %s";
      output_len += snprintf(output + output_len,
                             output_size - output_len,
                             format,
                             groups[group_total - 1 - group_i]);
    }
  }

  if (leading_zeros_group_count == group_total) {
    snprintf(output, output_size, "%s", ones[0]);
  }
}

int main(void) {
  struct testcase_t testcases[] = {
    {
      .input = "0",
      .expected = "zero",
    },
    {
      .input = "000",
      .expected = "zero",
    },
    {
      .input = "7",
      .expected = "seven",
    },
    {
      .input = "00007",
      .expected = "seven",
    },
    {
      .input = "19",
      .expected = "nineteen",
    },
    {
      .input = "019",
      .expected = "nineteen",
    },
    {
      .input = "20",
      .expected = "twenty",
    },
    {
      .input = "21",
      .expected = "twenty-one",
    },
    {
      .input = "99",
      .expected = "ninety-nine",
    },
    {
      .input = "100",
      .expected = "one hundred",
    },
    {
      .input = "00100",
      .expected = "one hundred",
    },
    {
      .input = "101",
      .expected = "one hundred and one",
    },
    {
      .input = "110",
      .expected = "one hundred and ten",
    },
    {
      .input = "112",
      .expected = "one hundred and twelve",
    },
    {
      .input = "120",
      .expected = "one hundred and twenty",
    },
    {
      .input = "143",
      .expected = "one hundred and forty-three",
    },
    {
      .input = "999",
      .expected = "nine hundred and ninety-nine",
    },
    {
      .input = "1000",
      .expected = "one thousand",
    },
    {
      .input = "00001000",
      .expected = "one thousand",
    },
    {
      .input = "1001",
      .expected = "one thousand, one",
    },
    {
      .input = "1010",
      .expected = "one thousand, ten",
    },
    {
      .input = "1043",
      .expected = "one thousand, forty-three",
    },
    {
      .input = "0000001043",
      .expected = "one thousand, forty-three",
    },
    {
      .input = "1100",
      .expected = "one thousand, one hundred",
    },
    {
      .input = "1101",
      .expected = "one thousand, one hundred and one",
    },
    {
      .input = "1143",
      .expected = "one thousand, one hundred and forty-three",
    },
    {
      .input = "9999",
      .expected = "nine thousand, nine hundred and ninety-nine",
    },
    {
      .input = "1000000",
      .expected = "one million",
    },
    {
      .input = "00001000000",
      .expected = "one million",
    },
    {
      .input = "1000001",
      .expected = "one million, one",
    },
    {
      .input = "1000100",
      .expected = "one million, one hundred",
    },
    {
      .input = "1001100",
      .expected = "one million, one thousand, one hundred",
    },
    {
      .input = "1147483647",
      .expected =
        "one billion, one hundred and forty-seven million, four hundred and "
        "eighty-three thousand, six hundred and forty-seven",
    },
    {
      .input = "0001147483647",
      .expected =
        "one billion, one hundred and forty-seven million, four hundred and "
        "eighty-three thousand, six hundred and forty-seven",
    },
    {
      .input = "123456789",
      .expected = "one hundred and twenty-three million, four hundred and "
                  "fifty-six thousand, seven hundred and eighty-nine",
    },
    {
      .input = "2000000000",
      .expected = "two billion",
    },
    {
      .input = "000002000000000",
      .expected = "two billion",
    },
    {
      .input = "2000001001",
      .expected = "two billion, one thousand, one",
    },
    {
      .input = "7828660194658220598",
      .expected =
        "seven quintillion, eight hundred and twenty-eight quadrillion, six "
        "hundred and sixty trillion, one hundred and ninety-four billion, six "
        "hundred and fifty-eight million, two hundred and twenty thousand, "
        "five hundred and ninety-eight",
    },
    {
      .input = "0007828660194658220598",
      .expected =
        "seven quintillion, eight hundred and twenty-eight quadrillion, six "
        "hundred and sixty trillion, one hundred and ninety-four billion, six "
        "hundred and fifty-eight million, two hundred and twenty thousand, "
        "five hundred and ninety-eight",
    },
  };

  size_t passed = 0;
  size_t total = sizeof(testcases) / sizeof(struct testcase_t);

  total = 0;
  for (size_t i = 0; i < 20; i++) {
    total++;
    // for (size_t i = 0; i < total; i++) {
    struct testcase_t testcase = testcases[i];
    char *input = testcase.input;
    char *expected = testcase.expected;
    char output[1000] = {0};
    size_t output_size = sizeof(output);

    number_wordinator(output, output_size, input);

    if (strcmp(output, expected) == 0) {
      passed++;
      printf("\033[1;42m PASS \033[0m \033[1m%s\033[0m\n", input);
    } else {
      printf("\033[1;41m FAIL \033[0m \033[1m%s\033[0m\n", input);
      printf("  \033[32mExpected\033[0m: %s\n", expected);
      printf("    \033[31mActual\033[0m: %s\n", output);
    }
  }

  size_t failed = total - passed;

  printf("\n\033[1;43m   REPORT   \033[0m\n");
  printf("Total:  \033[1m%zu\033[0m\n", total);
  if (passed > 0) {
    printf("Passed: \033[1;32m%zu\033[0m\n", passed);
  }
  if (failed > 0) {
    printf("Failed: \033[1;31m%zu\033[0m\n", failed);
  }
}
