#include "../s21_string.h"

void s21_decimalToHexadecimal(char *hex, unsigned long long int d, int isUp) {
  s21_size_t i = 0;
  if (d == 0) {
    hex[i++] = '0';
  } else {
    while (d > 0) {
      int x = d % 16;
      d /= 16;
      if (x < 10) {
        hex[i++] = x + '0';
      } else {
        hex[i++] = (isUp ? 'A' : 'a') + (x - 10);
      }
    }
  }
  hex[i] = '\0';
  s21_size_t lenHex = s21_strlen(hex);
  char res[lenHex + 1];
  for (s21_size_t j = 0; j < lenHex; j++) {
    res[j] = hex[lenHex - j - 1];
  }
  res[lenHex] = '\0';

  s21_strncpy(hex, res, lenHex + 1);
}

void s21_specification_x_X(char *str, unsigned long long int d, int isUp,
                           opt *options) {
  if (options->L || options->plus || options->space ||
      (options->zero && options->precision)) {
    options->error = 1;
  }
  char *hex = calloc(18 + 3, 1);
  s21_memset(hex, 0, 18 + 3);
  s21_decimalToHexadecimal(hex, d, isUp);
  if (options->sign && hex[0] != '0' && !options->precision &&
      (!options->zero || (options->zero && !options->width))) {
    char pushSign[18 + 3] = {0};
    pushSign[0] = '0';
    pushSign[1] = (isUp ? 'X' : 'x');
    s21_strncat(pushSign, hex, s21_strlen(hex));
    s21_strncpy(hex, pushSign, s21_strlen(pushSign));
  }
  if (options->precision && s21_strlen(hex) < (s21_size_t)options->precision) {
    hex = realloc(hex, options->precision);
    s21_add_zero_x_X(hex, options->precision, isUp, options);
  }
  s21_size_t lenHex = s21_strlen(hex);
  s21_size_t widthlen = options->width;
  char result[widthlen];
  s21_memset(result, 0, widthlen);
  if (options->width && widthlen > lenHex && !options->minus &&
      !options->zero) {
    for (s21_size_t i = widthlen, j = 0; i > lenHex; i--, j++) {
      result[j] = ' ';
    }
    s21_strncat(result, hex, lenHex);
    s21_strncat(str, result, widthlen);
  } else if (options->width && widthlen > lenHex && options->minus &&
             !options->zero) {
    s21_strncat(result, hex, lenHex);
    for (s21_size_t i = lenHex; i <= widthlen; i++) {
      result[i] = ' ';
    }
    s21_strncat(str, result, widthlen);
  } else if (options->width && widthlen > lenHex && options->zero &&
             !options->precision) {
    hex = realloc(hex, options->width);
    if (options->sign) {
      s21_add_zero_x_X(hex, options->width - 2, isUp, options);
    } else {
      s21_add_zero_x_X(hex, options->width, isUp, options);
    }
    s21_strncat(str, hex, widthlen);
  } else {
    s21_strncat(str, hex, lenHex);
  }
  free(hex);
}

void s21_add_zero_x_X(char *hex, int param, int isUp, opt *options) {
  s21_size_t prec = param;
  while (s21_strlen(hex) < prec) {
    char pushSign[prec];
    s21_memset(pushSign, 0, prec);
    pushSign[0] = '0';
    s21_strncat(pushSign, hex, s21_strlen(hex));
    s21_strncpy(hex, pushSign, s21_strlen(pushSign));
  }
  if (options->sign) {
    char pushSign[prec + 2];
    s21_memset(pushSign, 0, prec + 2);
    pushSign[0] = '0';
    pushSign[1] = (isUp ? 'X' : 'x');
    s21_strncat(pushSign, hex, s21_strlen(hex));
    s21_strncpy(hex, pushSign, s21_strlen(pushSign));
  }
}
