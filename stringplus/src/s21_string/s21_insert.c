#include "../s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  s21_size_t lenSrc = s21_strlen(src);
  s21_size_t lenStr = s21_strlen(str);
  char *res = malloc(lenSrc + lenStr + 1);
  if (src == s21_NULL || str == s21_NULL || start_index > lenStr) {
    res = s21_NULL;
  } else {
    for (s21_size_t i = 0; i < lenSrc; i++) {
      res[i] = src[i];
    }
    char temp[lenSrc - start_index];
    for (s21_size_t i = start_index, j = 0; i < lenSrc; i++, j++) {
      temp[j] = src[i];
    }
    for (s21_size_t i = start_index, j = 0; j < lenStr; i++, j++) {
      res[i] = str[j];
    }
    s21_size_t lenRes = s21_strlen(res);
    for (s21_size_t i = lenRes, j = 0; i < lenSrc + lenStr; i++, j++) {
      res[i] = temp[j];
    }
  }
  return (void *)res;
}