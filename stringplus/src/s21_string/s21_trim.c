#include "../s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  char *trimmed_str = s21_NULL;

  if (src != s21_NULL && trim_chars != s21_NULL) {
    const char *start = src;
    const char *end = src + s21_strlen(src) - 1;
    while (*start && s21_strchr(trim_chars, *start)) {
      start++;
    }

    while (end >= start && s21_strchr(trim_chars, *end)) {
      end--;
    }
    s21_size_t trimmed_len = end >= start ? (end - start + 1) : 0;

    trimmed_str = (char *)malloc(trimmed_len + 1);
    if (trimmed_str) {
      s21_strncpy(trimmed_str, start, trimmed_len);
      trimmed_str[trimmed_len] = '\0';
    }
  }

  return (void *)trimmed_str;
}
