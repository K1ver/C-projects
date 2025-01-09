#include "../s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  char *result = s21_NULL;

  if (str1 != s21_NULL && str2 != s21_NULL) {
    while (*str1 != '\0' && !result) {
      const char *temp = str2;
      while (*temp != '\0' && !result) {
        if (*str1 == *temp) result = (char *)str1;
        temp++;
      }
      str1++;
    }
  }

  return result;
}