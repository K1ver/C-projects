#include "../s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  static char *ptrLast = s21_NULL;
  if (str != s21_NULL) {
    ptrLast = str;
  }
  char *ptrEnd = ptrLast;
  char *ptrStart = ptrLast;
  if (ptrLast != s21_NULL) {
    while (*ptrEnd != '\0' && s21_strchr(delim, *ptrEnd)) {
      ptrEnd++;
    }
    ptrStart = ptrEnd;
    int isFind = 0;
    while (*ptrEnd != '\0' && !s21_strchr(delim, *ptrEnd)) {
      ptrEnd++;
      isFind = 1;
    }
    if (*ptrEnd != '\0') {
      *ptrEnd = '\0';
      ptrLast = ptrEnd + 1;
    } else {
      ptrLast = s21_NULL;
      if (!isFind) {
        ptrStart = s21_NULL;
      }
    }
  }
  return ptrStart;
}