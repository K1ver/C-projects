#include "../s21_string.h"

void *s21_to_upper(const char *str) {
  char *copy = s21_NULL;
  if (str != s21_NULL) {
    s21_size_t lenStr = s21_strlen(str);
    copy = malloc(lenStr + 1);
    for (s21_size_t i = 0; i < lenStr; i++) {
      if (str[i] >= 'a' && str[i] <= 'z') {
        copy[i] = str[i] - ('a' - 'A');
      } else {
        copy[i] = str[i];
      }
    }
  }
  return (void *)copy;
}