#include "../s21_string.h"

void s21_decimalToOctal(char *o, unsigned long long int d) {
  for (s21_size_t i = 0; i < 13; i++) {
    o[i] = (d % 8) + '0';
    d /= 8;
    if (d <= 0) break;
  }
  s21_size_t lenOctal = s21_strlen(o);
  char res[lenOctal + 1];
  s21_memset(res, 0, lenOctal);
  for (s21_size_t i = 0, j = lenOctal - 1; i < lenOctal; i++, j--) {
    res[i] = o[j];
  }
  res[lenOctal] = '\0';
  s21_strncpy(o, res, s21_strlen(res));
}

void s21_specification_o(char *str, unsigned long long int d, opt *options) {
  if (options->L || options->plus || options->space ||
      (options->zero && options->precision)) {
    options->error = 1;
  }
  char *o = calloc(12 + 2, 1);
  s21_memset(o, 0, 12 + 2);
  s21_decimalToOctal(o, d);
  if (options->sign && o[0] != '0' && !options->precision) {
    char pushSign[12 + 2] = {0};
    pushSign[0] = '0';
    s21_strncat(pushSign, o, s21_strlen(o));
    s21_strncpy(o, pushSign, s21_strlen(pushSign));
  }
  if (options->precision && s21_strlen(o) < (s21_size_t)options->precision) {
    o = realloc(o, options->precision);
    s21_precision_o(o, options);
  }
  s21_size_t lenOctal = s21_strlen(o);
  s21_size_t widthlen = options->width;
  char result[widthlen];
  s21_memset(result, 0, widthlen);
  if (options->width && widthlen > lenOctal && !options->minus &&
      (!options->zero || (options->zero && !options->width))) {
    for (s21_size_t i = widthlen, j = 0; i > lenOctal; i--, j++) {
      result[j] = ' ';
    }
    s21_strncat(result, o, lenOctal);
    s21_strncat(str, result, widthlen);
  } else if (options->width && widthlen > lenOctal && options->minus &&
             !options->zero) {
    s21_strncat(result, o, lenOctal);
    for (s21_size_t i = lenOctal; i <= widthlen; i++) {
      result[i] = ' ';
    }
    s21_strncat(str, result, widthlen);
  } else if (options->width && widthlen > lenOctal && options->zero) {
    for (s21_size_t i = widthlen, j = 0; i > lenOctal; i--, j++) {
      result[j] = '0';
    }
    s21_strncat(result, o, lenOctal);
    s21_strncat(str, result, widthlen);
  } else {
    s21_strncat(str, o, lenOctal);
  }
  free(o);
}

void s21_precision_o(char *o, opt *options) {
  while (s21_strlen(o) < (s21_size_t)options->precision) {
    char pushSign[options->precision];
    s21_memset(pushSign, 0, options->precision);
    pushSign[0] = '0';
    s21_strncat(pushSign, o, s21_strlen(o));
    s21_strncpy(o, pushSign, s21_strlen(pushSign));
  }
}
