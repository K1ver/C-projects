#include "../s21_string.h"

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  char *d = (char *)dest;
  const char *s = (const char *)src;
  if (s != s21_NULL) {
    if (s21_strlen(s) > n) {
      for (s21_size_t i = 0; i < n && s[i]; i++) {
        d[i] = s[i];
      }
    } else {
      s21_memset(d, 0, s21_strlen(d));
      for (s21_size_t i = 0; i < s21_strlen(s); i++) {
        d[i] = s[i];
      }
    }
  }
  return (void *)dest;
}
