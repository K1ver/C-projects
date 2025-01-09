#include "../s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  const unsigned char *buffer = (const unsigned char *)str;
  const unsigned char *result = s21_NULL;
  for (s21_size_t i = 0; i < n; i++) {
    if (buffer[i] == (unsigned char)c) {
      result = (void *)&buffer[i];
    }
  }
  return (void *)result;
}
