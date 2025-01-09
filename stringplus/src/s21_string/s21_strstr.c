#include "../s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  char *result = s21_NULL;

  if (haystack != s21_NULL && needle != s21_NULL) {
    if (*needle == '\0') {
      result = (char *)haystack;
    } else {
      const char *h, *n;
      for (; *haystack != '\0' && !result; haystack++) {
        h = haystack;
        n = needle;
        while (*n != '\0' && *h == *n) {
          h++;
          n++;
        }
        if (*n == '\0') {
          result = (char *)haystack;
        }
      }
    }
  }

  return result;
}