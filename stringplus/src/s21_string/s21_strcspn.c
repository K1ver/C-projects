#include "../s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t lenStr1 = s21_strlen(str1);
  s21_size_t lenStr2 = s21_strlen(str2);
  s21_size_t countBeforeCh = 0;
  int isFoundCh = 0;
  for (s21_size_t i = 0; i < lenStr1; i++) {
    for (s21_size_t j = 0; j < lenStr2; j++) {
      if (str1[i] == str2[j]) {
        isFoundCh = 1;
      }
    }
    if (!isFoundCh) {
      countBeforeCh++;
    }
  }
  return countBeforeCh;
}