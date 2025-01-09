#include "../s21_string.h"

void *s21_memset(void *str, int c, s21_size_t n) {
  char *s = (char *)str;
  if (s != s21_NULL) {
    for (s21_size_t i = 0; i < n; i++) {
      unsigned char count = (unsigned char)c;
      s[i] = count;
    }
  }

  return (void *)s;
}
