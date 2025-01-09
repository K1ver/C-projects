#include "../s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  s21_size_t lenDest = s21_strlen(dest);
  s21_size_t lenSrc = s21_strlen(src);
  for (s21_size_t i = 0; i < n; i++) {
    if (i < lenSrc) {
      dest[lenDest + i] = src[i];
      dest[lenDest + i + 1] = '\0';
    }
  }
  return dest;
}