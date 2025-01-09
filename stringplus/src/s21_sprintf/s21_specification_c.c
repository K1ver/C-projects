#include "../s21_string.h"

void s21_specification_c(char *str, int c, opt *options) {
  if (options->plus || options->space || options->zero || options->L ||
      options->sign || options->precision || options->h) {
    options->error = 1;
  }
  unsigned int t = c;

  char result[2] = {0};
  if (t && !options->minus) {
    result[0] = t;
    result[1] = '\0';
  } else {
    result[0] = t;
  }
  s21_size_t totallen = options->width;
  char copyresult[totallen];
  s21_memset(copyresult, 0, totallen);
  if (!options->minus && totallen) {
    for (s21_size_t i = 0; i < totallen - 1; i++) {
      copyresult[i] = ' ';
    }
    copyresult[totallen - 1] = result[0];
    copyresult[totallen] = '\0';
    s21_strncat(str, copyresult, totallen);
  } else if (options->minus && totallen && options->width) {
    copyresult[0] = result[0];
    for (s21_size_t i = 1; i < totallen; i++) {
      copyresult[i] = ' ';
    }
    copyresult[totallen] = '\0';
    s21_strncat(str, copyresult, totallen);
  } else {
    int lenstr = s21_strlen(result);
    s21_strncat(str, result, lenstr);
  }
}