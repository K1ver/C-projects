#include "../s21_string.h"

void s21_specification_s(char *str, const char *value, opt *options) {
  if (options->sign || options->L || options->zero || options->plus ||
      options->space) {
    options->error = 1;
    return;
  }

  char temp[4096] = {0};

  if (options->precision) {
    s21_size_t len_to_copy = (s21_size_t)options->precision < s21_strlen(value)
                                 ? (size_t)options->precision
                                 : s21_strlen(value);
    s21_strncat(temp, value, len_to_copy);
  } else {
    s21_strncat(temp, value, s21_strlen(value));
  }

  int src_len = s21_strlen(temp);
  int padding = (options->width > src_len) ? options->width - src_len : 0;

  if (options->minus && options->width && options->width > src_len) {
    s21_strncat(str, temp, s21_strlen(temp));
    for (int i = 0; i < padding; i++) {
      str[src_len + i] = ' ';
    }
  } else if (!options->minus && options->width && options->width > src_len) {
    for (int i = 0; i < padding; i++) {
      str[i] = ' ';
    }
    s21_strncat(str + padding, temp, s21_strlen(temp));
  } else {
    s21_strncat(str, temp, s21_strlen(temp));
  }
}
