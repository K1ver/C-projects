#include "../s21_string.h"

void s21_specification_d_u(long long int d, char *str, opt *options, int isU) {
  if (options->sign || options->L || (options->precision && options->zero) ||
      (isU && (options->plus || options->space))) {
    options->error = 1;
  }
  char *tempin = calloc(11 + 1, 1);
  int isNeg = s21_intToStr(d, tempin);
  if ((options->plus || options->space || isNeg) && !options->precision &&
      (!options->zero || (options->zero && !options->width)) && !isU) {
    char pushSign[11 + 1];
    s21_memset(pushSign, 0, 11 + 1);
    if (options->plus && !isNeg) {
      pushSign[0] = '+';
    } else if (options->space && !isNeg) {
      pushSign[0] = ' ';
    } else if (isNeg) {
      pushSign[0] = '-';
    }
    s21_strncat(pushSign, tempin, s21_strlen(tempin));
    s21_strncpy(tempin, pushSign, s21_strlen(pushSign));
  }
  if (options->precision &&
      s21_strlen(tempin) < (s21_size_t)options->precision) {
    tempin = realloc(tempin, options->precision);
    s21_add_zero_d_u(tempin, options->precision, options, isNeg, isU);
  }
  s21_size_t lenInt = s21_strlen(tempin);
  s21_size_t widthlen = options->width;
  char result[widthlen];
  s21_memset(result, 0, widthlen);
  if (options->width && widthlen > lenInt && !options->minus &&
      !options->zero) {
    for (s21_size_t i = widthlen, j = 0; i > lenInt; i--, j++) {
      result[j] = ' ';
    }
    s21_strncat(result, tempin, lenInt);
    s21_strncat(str, result, widthlen);
  } else if (options->width && widthlen > lenInt && options->minus &&
             !options->zero) {
    s21_strncat(result, tempin, lenInt);
    for (s21_size_t i = lenInt; i <= widthlen; i++) {
      result[i] = ' ';
    }
    s21_strncat(str, result, widthlen);
  } else if (options->width && widthlen > lenInt && options->zero) {
    tempin = realloc(tempin, options->width);
    s21_add_zero_d_u(tempin, options->width, options, isNeg, isU);
    s21_strncat(str, tempin, widthlen);
  } else {
    s21_strncat(str, tempin, lenInt);
  }
  free(tempin);
}

void s21_reverseString(char *string, int length) {
  for (int start = 0, end = length - 1; start < end; start++, end--) {
    char temp = string[start];
    string[start] = string[end];
    string[end] = temp;
  }
}

int s21_intToStr(long long int d, char *str) {
  int isNeg = 0;
  int i = 0;

  if (d < 0) {
    isNeg = 1;
    d = -d;
  }

  if (d == 0) {
    str[i++] = '0';
  } else {
    while (d > 0) {
      str[i++] = d % 10 + '0';
      d = d / 10;
    }
  }
  str[i] = '\0';

  s21_reverseString(str, i);

  return isNeg;
}

void s21_add_zero_d_u(char *d, int param, opt *options, int isNeg, int isU) {
  s21_size_t prec = param;
  if ((options->plus || options->space || isNeg) && !isU) {
    prec--;
  }
  while (s21_strlen(d) < prec) {
    char pushSign[prec];
    s21_memset(pushSign, 0, prec);
    pushSign[0] = '0';
    s21_strncat(pushSign, d, s21_strlen(d));
    s21_strncpy(d, pushSign, s21_strlen(pushSign));
  }
  if ((options->plus || options->space || isNeg) && !isU) {
    char pushSign[prec + 1];
    s21_memset(pushSign, 0, prec + 1);
    if (options->plus && !isNeg) {
      pushSign[0] = '+';
    } else if (options->space && !isNeg) {
      pushSign[0] = ' ';
    } else if (isNeg) {
      pushSign[0] = '-';
    }
    s21_strncat(pushSign, d, s21_strlen(d));
    s21_strncpy(d, pushSign, s21_strlen(pushSign));
  }
}
