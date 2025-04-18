#include <stdio.h>
#include <string.h>

const char *get_digit_word(char digit) {
  switch (digit) {
    case '1': return "one";
    case '2': return "two";
    case '3': return "three";
    case '4': return "four";
    case '5': return "five";
    case '6': return "six";
    case '7': return "seven";
    case '8': return "eight";
    case '9': return "nine";
    default:  return "";
  }
}

const char *get_digitty_word(char digit) {
  switch (digit) {
    case '1': return "ten";
    case '2': return "twenty";
    case '3': return "thirty";
    case '4': return "forty";
    case '5': return "fifty";
    case '6': return "sixty";
    case '7': return "seventy";
    case '8': return "eighty";
    case '9': return "ninety";
    default:  return "";
  }
}

const char *get_digitteen_word(char digit) {
  switch (digit) {
    case '1': return "eleven";
    case '2': return "twelve";
    case '3': return "thirteen";
    case '4': return "fourteen";
    case '5': return "fifteen";
    case '6': return "sixteen";
    case '7': return "seventeen";
    case '8': return "eighteen";
    case '9': return "nineteen";
    default:  return "";
  }
}

const char *get_digit_base_word(int index, int len) {
  int pos = len - index;
  if (pos == 3) return "hundred";
  if (4 <= pos && pos <= 6) return "thousand";
  if (7 <= pos && pos <= 9) return "million";
  if (10 <= pos && pos <= 12) return "billion";
  if (13 <= pos && pos <= 15) return "trillion";
  if (16 <= pos && pos <= 18) return "quadrillion";
  if (19 <= pos && pos <= 21) return "quintillion";
  return "";
}

void number_wordinator(char *words, int words_size, char *number) {
  const int MAX_DIGIT_GROUP_SIZE = 3;
  const int digit_count = strlen(number);
  const int digit_remainder_count = digit_count % MAX_DIGIT_GROUP_SIZE;
  const int missing_digit_in_first_group_count =
    digit_remainder_count == 0 ? 0
                               : (MAX_DIGIT_GROUP_SIZE - digit_remainder_count);
  const int group_count = digit_remainder_count == 0
                            ? (digit_count / MAX_DIGIT_GROUP_SIZE)
                            : ((digit_count / MAX_DIGIT_GROUP_SIZE) + 1);

  int words_written_size = 0;

  for (int group_i = 0; group_i < group_count; group_i++) {
    int start_i = group_i == 0 ? 0
                               : ((MAX_DIGIT_GROUP_SIZE * group_i) -
                                  missing_digit_in_first_group_count);
    int end_i = group_i == 0
                  ? (MAX_DIGIT_GROUP_SIZE - missing_digit_in_first_group_count)
                  : (start_i + MAX_DIGIT_GROUP_SIZE);
    int group_len = end_i - start_i;
    char *group_suffix_word = group_i != 0 ? ", " : "";

    char tmp_words[100] = {0};
    int tmp_words_size = sizeof(tmp_words);

    if (group_len == 1) {
      char digit = number[start_i];
      int written_size = snprintf(tmp_words,
                                  tmp_words_size,
                                  "%s%s %s",
                                  group_suffix_word,
                                  get_digit_word(digit),
                                  get_digit_base_word(start_i, digit_count));
      if (written_size < 0 || written_size >= tmp_words_size) {
        break;
      }
    }

    if (group_len == 2) {
      // TODO: Handle the 2nd digit is 0
      char first_digit = number[start_i];
      char second_digit = number[start_i + 1];

      const char *base_word = get_digit_base_word(start_i, digit_count);

      if (first_digit == '1') {
        int written_size = snprintf(tmp_words,
                                    tmp_words_size,
                                    "%s%s %s",
                                    group_suffix_word,
                                    get_digitteen_word(second_digit),
                                    get_digit_base_word(start_i, digit_count));
        if (written_size < 0 || written_size >= tmp_words_size) {
          break;
        }
      } else {
        int written_size = snprintf(tmp_words,
                                    tmp_words_size,
                                    "%s%s-%s %s",
                                    group_suffix_word,
                                    get_digitty_word(first_digit),
                                    get_digit_word(second_digit),
                                    get_digit_base_word(start_i, digit_count));
        if (written_size < 0 || written_size >= tmp_words_size) {
          break;
        }
      }
    }

    if (group_len == 3) {
      // TODO: Handle the 1st digit is 0
      // TODO: Handle the 2nd digit is 0
      // TODO: Handle the 3rd digit is 0
      // TODO: Handle both 1st and 2nd digit is 0
      // TODO: Handle both 1st and 3rd digit is 0
      // TODO: Handle both 2nd and 3rd digit is 0
      // TODO: Handle the 2nd digit is 1
      char first_digit = number[start_i];
      char second_digit = number[start_i + 1];
      char third_digit = number[start_i + 2];

      int written_size;

      if (group_i == group_count - 1) {
        written_size = snprintf(tmp_words,
                                tmp_words_size,
                                "%s%s hundred and %s-%s",
                                group_suffix_word,
                                get_digit_word(first_digit),
                                get_digitty_word(second_digit),
                                get_digit_word(third_digit));
      } else {
        written_size = snprintf(tmp_words,
                                tmp_words_size,
                                "%s%s hundred and %s-%s %s",
                                group_suffix_word,
                                get_digit_word(first_digit),
                                get_digitty_word(second_digit),
                                get_digit_word(third_digit),
                                get_digit_base_word(start_i, digit_count));
      }
      if (written_size < 0 || written_size >= tmp_words_size) {
        break;
      }
    }

    int remaining_size = words_size - words_written_size;
    if (remaining_size <= 0) {
      break;
    }

    int written_size =
      snprintf(words + words_written_size, remaining_size, "%s", tmp_words);
    if (written_size < 0 || written_size >= remaining_size) {
      break;
    }

    words_written_size += written_size;
  }
}

struct testcase_t {
  char *number;
  char *expected;
};

int main(void) {
  struct testcase_t testcases[] = {
    {
      .number = "0",
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
      .number = "123456789",
      .expected = "one hundred and twenty-three million, four hundred and "
                  "fifty-six thousand, seven hundred and eighty-nine",
    },
    {
      .number = "2000000000",
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
  };

  int passed_count = 0;
  int testcases_total = sizeof(testcases) / sizeof(struct testcase_t);
  for (int i = 0; i < testcases_total; i++) {
    struct testcase_t testcase = testcases[i];
    char *number = testcase.number;
    char *expected = testcase.expected;
    char words[1000] = {0};
    int words_size = sizeof(words);

    number_wordinator(words, words_size, number);

    if (strcmp(words, expected) == 0) {
      passed_count++;
      printf("\n\033[1;42;39m PASS \033[0m \033[1m%s\033[0m\n", number);
    } else {
      printf("\n\033[1;41;39m FAIL \033[0m \033[1m%s\033[0m\n", number);
      printf("  \033[1;32m EXPECTED\033[0m: %s\n", expected);
      printf("    \033[1;31m ACTUAL\033[0m: %s\n", words);
    }

    if (passed_count == testcases_total) {
    } else {
      printf("\n\033[1m=> \033[0m\033[1;32mPASSED: %d/%d\033[0m\n", passed_count, testcases_total);
    }
  }
}
