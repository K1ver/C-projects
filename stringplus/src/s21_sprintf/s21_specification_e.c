#include "../s21_string.h"

void s21_specification_e(long double floatNumber, char *floatBuffer,
                         opt *options, int isUp) {
  int exponent = 0;
  int depth = 0;
  int shift = 0;
  long double mantissa = floatNumber;
  long double cpymantissa = mantissa;
  if ((int)cpymantissa == 0) {
    while ((int)cpymantissa == 0) {
      cpymantissa *= 10;
      depth++;
    }
    depth++;
  } else {
    while ((int)cpymantissa != 0) {
      int temp = (int)cpymantissa % 10;
      cpymantissa /= 10;
      cpymantissa += temp / 10;
      shift++;
      depth = 2;
    }
    mantissa = cpymantissa;
  }
  if (options->precision != 0) {
    if (mantissa < 0) {
      mantissa = mantissa - (5 / pow(10, options->precision + depth));
    } else {
      mantissa = mantissa + (5 / pow(10, options->precision + depth));
    }
  }

  while (shift != 0) {
    int temp = (int)mantissa * 10;
    mantissa -= (int)mantissa;
    mantissa *= 10;
    mantissa += temp;
    shift--;
  }

  if (mantissa != 0.0) {
    while (fabsl(mantissa) >= 10.0) {
      mantissa /= 10.0;
      exponent++;
    }
    while (fabsl(mantissa) <= 1.0) {
      mantissa *= 10.0;
      exponent--;
    }
  }

  int sign = (floatNumber < 0) ? -1 : 1;

  mantissa *= sign;

  int ipart = (int)mantissa;
  long double fpart = fabsl(mantissa - ipart);
  char mantissaStr[1024];
  int i = s21_itoa(ipart, mantissaStr, 0);
  if (fpart != 0.0 && options->precision) {
    mantissaStr[i++] = '.';
    for (int j = 0; j < options->precision; j++) {
      fpart *= 10;
      int digit = (int)fpart;
      mantissaStr[i++] = digit + '0';
      fpart -= digit;
    }
  }
  mantissaStr[i] = '\0';

  char exponentStr[10];
  if (isUp) {
    exponentStr[0] = 'E';
  } else
    exponentStr[0] = 'e';

  if (exponent >= 0) {
    exponentStr[1] = '+';
  } else {
    exponentStr[1] = '-';
  }

  s21_itoa(abs(exponent), exponentStr + 2, 2);

  char sign_char = 0;
  if (floatNumber < 0) {
    sign_char = '-';
    floatNumber = -floatNumber;
  } else if (options->plus) {
    sign_char = '+';
  } else if (options->space) {
    sign_char = ' ';
  }
  char temp[4096] = {0};
  s21_strncat(temp, mantissaStr, s21_strlen(mantissaStr));
  s21_strncat(temp, exponentStr, s21_strlen(exponentStr));

  int width = options->width;
  int string_len = s21_strlen(temp);
  char *result = calloc(width + 1, 1);
  s21_memset(result, 0, width);
  int total_len = string_len + (sign_char ? 1 : 0);
  int padding_len = width > total_len ? width - total_len : 0;
  int pad = 1;

  if (options->minus && padding_len) {
    if (sign_char) {
      s21_strncat(result, &sign_char, 1);
    }
    s21_strncat(result, temp, string_len);
    for (int i = 0; i < padding_len; i++) {
      s21_strncat(result, " ", pad);
    }
    s21_strncat(floatBuffer, result, options->width);
  } else if (options->zero && options->width && padding_len) {
    if (sign_char) {
      s21_strncat(result, &sign_char, 1);
    }
    for (int i = 0; i < padding_len; i++) {
      s21_strncat(result, "0", pad);
    }
    s21_strncat(result, temp, string_len);
    s21_strncat(floatBuffer, result, options->width);
  } else if (options->width && padding_len) {
    for (int i = 0; i < padding_len; i++) {
      s21_strncat(result, " ", pad);
    }
    if (sign_char) {
      s21_strncat(result, &sign_char, 1);
    }
    s21_strncat(result, temp, string_len);
    s21_strncat(floatBuffer, result, options->width);
  } else {
    if (sign_char) {
      s21_strncat(floatBuffer, &sign_char, 1);
    }
    s21_strncat(floatBuffer, temp, string_len);
  }
  free(result);
}

int s21_itoa(int x, char str[], int d) {
  int i = 0;

  if (x == 0) {
    str[i++] = '0';
  } else {
    while (x) {
      str[i++] = (x % 10) + '0';
      x = x / 10;
    }
  }
  while (i < d) {
    str[i++] = '0';
  }
  s21_reverseString(str, i);
  str[i] = '\0';
  return i;
}
