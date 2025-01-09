#include "../s21_string.h"

void s21_specification_p(char *str, void *p, opt *options) {
  if (options->plus || options->space || options->zero || options->L ||
      options->sign || options->precision || options->h || options->l) {
    options->error = 1;
  }
  char buf[15] = "0x000000000000";
  int k = 13;
  for (void *j = p; j; j = (void *)(((size_t)j) >> 4), --k) {
    unsigned int dig = ((size_t)j) % 0x10;
    if (dig < 10)
      buf[k] = '0' + dig;
    else
      buf[k] = 'a' + (dig - 10);
  }
  s21_del_char_p(buf);
  int widthlen = options->width;
  char result[widthlen];
  s21_memset(result, 0, widthlen);
  int lenBuf = s21_strlen(buf);
  if (options->width && widthlen >= lenBuf && !options->minus) {
    for (int i = 0; i < widthlen - lenBuf; i++) {
      result[i] = ' ';
    }
    s21_strncat(str, result, widthlen);
    s21_strncat(str, buf, lenBuf);
  } else if (options->width && widthlen >= lenBuf && options->minus) {
    s21_strncat(str, buf, lenBuf);
    for (int i = 0; i < widthlen - lenBuf; i++) {
      result[i] = ' ';
    }
    s21_strncat(str, result, widthlen);
  } else {
    s21_strncat(str, buf, 15);
  }
}

void s21_del_char_p(char *buff) {
  while (buff[2] == '0') {
    s21_size_t i;
    for (i = 2; i < s21_strlen(buff); i++) {
      buff[i] = buff[i + 1];
    }
    buff[i] = '\0';
  }
}