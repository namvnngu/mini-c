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

int main(void) {
  const char *NUMBER = "1147483647";
  const int DIGIT_COUNT = strlen(NUMBER);
  const int MAX_GROUP_SIZE = 3;
  const int DIGIT_REMAINDER_COUNT = DIGIT_COUNT % MAX_GROUP_SIZE;
  const int MISSING_DIGIT_IN_FIRST_GROUP_COUNT =
      DIGIT_REMAINDER_COUNT == 0 ? 0 : (MAX_GROUP_SIZE - DIGIT_REMAINDER_COUNT);
  const int GROUP_COUNT = DIGIT_REMAINDER_COUNT == 0
                              ? (DIGIT_COUNT / MAX_GROUP_SIZE)
                              : ((DIGIT_COUNT / MAX_GROUP_SIZE) + 1);

  char words[1000] = {0};
  int words_size = sizeof(words);
  int words_written_size = 0;

  for (int group_i = 0; group_i < GROUP_COUNT; group_i++) {
    int start_i =
        group_i == 0
            ? 0
            : ((MAX_GROUP_SIZE * group_i) - MISSING_DIGIT_IN_FIRST_GROUP_COUNT);
    int end_i = group_i == 0
                    ? (MAX_GROUP_SIZE - MISSING_DIGIT_IN_FIRST_GROUP_COUNT)
                    : (start_i + MAX_GROUP_SIZE);
    int group_len = end_i - start_i;
    char *group_suffix_word = group_i != 0 ? ", " : "";

    char tmp_words[100] = {0};
    int tmp_words_size = sizeof(tmp_words);

    if (group_len == 1) {
      char digit = NUMBER[start_i];
      int written_size = snprintf(tmp_words,
                                  tmp_words_size,
                                  "%s%s %s",
                                  group_suffix_word,
                                  get_digit_word(digit),
                                  get_digit_base_word(start_i, DIGIT_COUNT));
      if (written_size < 0 || written_size >= tmp_words_size) {
        break;
      }
    }

    if (group_len == 2) {
      // TODO: Hanlde the 2nd digit is 0
      char first_digit = NUMBER[start_i];
      char second_digit = NUMBER[start_i + 1];

      const char *base_word = get_digit_base_word(start_i, DIGIT_COUNT);

      if (first_digit == '1') {
        int written_size = snprintf(tmp_words,
                                    tmp_words_size,
                                    "%s%s %s",
                                    group_suffix_word,
                                    get_digitteen_word(second_digit),
                                    get_digit_base_word(start_i, DIGIT_COUNT));
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
                                    get_digit_base_word(start_i, DIGIT_COUNT));
        if (written_size < 0 || written_size >= tmp_words_size) {
          break;
        }
      }
    }

    if (group_len == 3) {
      // TODO: Hanlde the 1st digit is 0
      // TODO: Hanlde the 2nd digit is 0
      // TODO: Hanlde the 3rd digit is 0
      // TODO: Hanlde both 1st and 2nd digit is 0
      // TODO: Hanlde both 1st and 3rd digit is 0
      // TODO: Hanlde both 2nd and 3rd digit is 0
      // TODO: Handle the 2nd digit is 1
      char first_digit = NUMBER[start_i];
      char second_digit = NUMBER[start_i + 1];
      char third_digit = NUMBER[start_i + 2];

      int written_size;

      if (group_i == GROUP_COUNT - 1) {
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
                                get_digit_base_word(start_i, DIGIT_COUNT));
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

  const char *expected =
      "one billion, one hundred and forty-seven million, four hundred and "
      "eighty-three thousand, six hundred and forty-seven";
  if (strcmp(words, expected) == 0) {
    printf("\n\033[1;42;39m PASS \033[0m \033[1m%s\033[0m\n", NUMBER);
    printf("  %s\n", words);
  } else {
    printf("\n\033[1;41;39m FAIL \033[0m \033[1m%s\033[0m\n", NUMBER);
    printf("  \033[1;32m EXPECTED\033[0m: %s\n", expected);
    printf("    \033[1;31m ACTUAL\033[0m: %s\n", words);
  }
}
