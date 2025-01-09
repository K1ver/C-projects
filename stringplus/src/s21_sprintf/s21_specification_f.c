#include "../s21_string.h"

void s21_reverse(char *str, int len) {
  int i = 0, j = len - 1, temp;
  while (i < j) {
    temp = str[i];
    str[i] = str[j];
    str[j] = temp;
    i++;
    j--;
  }
}

void s21_floatingPointToStr(char *res, long double fpart, int afterpoint) {
  for (int i = 0; i < afterpoint; i++) {
    fpart = fpart * 10;
    int temp = fpart / 10;
    fpart -= temp * 10;
    res[i] = (int)fpart + '0';
  }
}

int s21_floatDecimalToStr(unsigned long long int x, char *str, int d) {
  int i = 0;
  while (x) {
    str[i++] = (x % 10) + '0';
    x = x / 10.0;
  }
  while (i < d) str[i++] = '0';

  s21_reverse(str, i);
  str[i] = '\0';
  return i;
}

void s21_ftoa(long double n, char *res, opt *options) {
  long double fpart;
  int ipart;

  if (options->L) {
    long long ipart_ll = (long long)n;
    long double fpart_ld = n - (long long)ipart_ll;
    ipart = (int)ipart_ll;
    fpart = fpart_ld;
  } else {
    int ipart_int = (int)n;
    double fpart_f = n - (int)ipart_int;
    ipart = ipart_int;
    fpart = fpart_f;
  }
  int i = s21_floatDecimalToStr(ipart, res, 0);

  if (options->precision != 0) {
    res[i] = '.';
    s21_floatingPointToStr(res + i + 1, fpart, options->precision);
  } else if (options->precision == 0 && options->sign) {
    res[i] = '.';
  }
}

void s21_specification_f(char *baseStr, long double n, opt *options) {
  if (options->h || options->l) {
    options->error = 1;
  }

  if (options->precision != 0) {
    if (n > 0) {
      n = n + (5 / pow(10, options->precision + 1));
    } else {
      n = n - (5 / pow(10, options->precision + 1));
    }
  } else {
    if (n - (int)n >= 0.5) {
      n = n + 0.5;
    }
  }
  if (options->plus && options->space) options->error = 1;
  if (options->zero && options->minus) options->error = 1;
  char sign_char = 0;
  if (n < 0) {
    sign_char = '-';
    n = -n;
  } else if (options->plus) {
    sign_char = '+';
  } else if (options->space) {
    sign_char = ' ';
  }

  char temp[4096] = {0};
  s21_ftoa(n, temp, options);

  int stringlen = s21_strlen(temp);
  char result[options->width];
  s21_memset(result, 0, options->width);
  int total_len = stringlen + (sign_char ? 1 : 0);
  int padding_len = options->width > total_len ? options->width - total_len : 0;
  int pad = 1;
  if (options->minus) {
    if (sign_char) {
      s21_strncat(result, &sign_char, 1);
    }
    s21_strncat(result, temp, stringlen);
    for (int i = 0; i < padding_len; i++) {
      s21_strncat(result, " ", pad);
    }
    s21_strncat(baseStr, result, options->width);
  } else if (options->zero && options->width) {
    if (sign_char) {
      s21_strncat(result, &sign_char, 1);
    }
    for (int i = 0; i < padding_len; i++) {
      s21_strncat(result, "0", pad);
    }
    s21_strncat(result, temp, stringlen);
    s21_strncat(baseStr, result, options->width);
  } else if (options->width) {
    for (int i = 0; i < padding_len; i++) {
      s21_strncat(result, " ", pad);
    }
    if (sign_char) {
      s21_strncat(result, &sign_char, 1);
    }
    s21_strncat(result, temp, stringlen);
    s21_strncat(baseStr, result, options->width);
  } else {
    if (sign_char) {
      s21_strncat(baseStr, &sign_char, 1);
    }
    s21_strncat(baseStr, temp, stringlen);
  }
}
