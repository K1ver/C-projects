#include "../s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
  va_list(args);
  va_start(args, format);
  s21_strncpy(str, "", s21_strlen(str));
  s21_parser_sprintf(str, format, &args);
  va_end(args);
  return s21_strlen(str);
}

//%[флаг][ширина][длина]спецификатор.
void s21_parser_sprintf(char *str, const char *format, va_list *args) {
  while (*format) {
    opt options = {0};
    if (*format != '%') {
      s21_add_char(str, *format);
      format++;
    } else {
      format++;
      while (s21_strchr("-+ #0", *format) && !options.error) {
        s21_check_flags_sprintf(*format++, &options);
      }
      if (s21_strchr("1234567890*", *format) && !options.error) {
        int count = s21_check_width_sprintf(format, &options, args);
        if (!options.error) {
          if (count == -1) {
            format++;
          } else {
            format += count;
          }
        }
      }
      if (s21_strchr(".", *format) && !options.error) {
        int count = s21_check_precision_sprintf(format++, &options, args);
        if (!options.error) {
          if (count == -1) {
            format++;
          } else {
            format += count;
          }
        }
      }
      while (s21_strchr("hlL", *format) && !options.error) {
        s21_check_lenght_sprintf(*format++, &options);
      }
      if (!options.error) {
        s21_check_specification_sprintf(str, *format++, &options, args);
      }
      if (options.error) {
        s21_strncpy(str, "", s21_strlen(str));
        break;
      }
    }
  }
}

void s21_add_char(char *str, char c) { str[s21_strlen(str)] = c; }

void s21_check_specification_sprintf(char *str, const char specification,
                                     opt *options, va_list *arg) {
  switch (specification) {
    case 'c':
      s21_specification_c(str, va_arg(*arg, int), options);
      break;
    case 'd':
      if (options->h) {
        s21_specification_d_u((short int)va_arg(*arg, int), str, options, 0);
      } else if (options->l) {
        s21_specification_d_u((long int)va_arg(*arg, long int), str, options,
                              0);
      } else {
        s21_specification_d_u(va_arg(*arg, int), str, options, 0);
      }
      break;
    case 'f':
      if (options->precision == -1) {
        options->precision = 0;
      } else if (options->precision == 0) {
        options->precision = 6;
      }
      if (options->L) {
        s21_specification_f(str, va_arg(*arg, long double), options);
      } else {
        s21_specification_f(str, va_arg(*arg, double), options);
      }
      break;
    case 's':
      s21_specification_s(str, va_arg(*arg, const char *), options);
      break;
    case 'u':
      if (options->h) {
        s21_specification_d_u((unsigned short int)va_arg(*arg, unsigned int),
                              str, options, 0);
      } else if (options->l) {
        s21_specification_d_u(
            (unsigned long int)va_arg(*arg, unsigned long int), str, options,
            0);
      } else {
        s21_specification_d_u(va_arg(*arg, unsigned int), str, options, 0);
      }
      break;
    case 'g':

      break;
    case 'G':

      break;
    case 'e':
      if (options->precision == -1) {
        options->precision = 0;
      } else if (options->precision == 0) {
        options->precision = 6;
      }
      if (options->L) {
        s21_specification_e(va_arg(*arg, long double), str, options, 0);
      } else {
        s21_specification_e(va_arg(*arg, double), str, options, 0);
      }

      break;
    case 'E':
      if (options->precision == -1) {
        options->precision = 0;
      } else if (options->precision == 0) {
        options->precision = 6;
      }
      if (options->L) {
        s21_specification_e(va_arg(*arg, long double), str, options, 1);
      } else {
        s21_specification_e(va_arg(*arg, double), str, options, 1);
      }

      break;
    case 'x':
      if (options->h) {
        s21_specification_x_X(
            str, (unsigned short int)va_arg(*arg, unsigned int), 0, options);
      } else if (options->l) {
        s21_specification_x_X(
            str, (unsigned long int)va_arg(*arg, unsigned long int), 0,
            options);
      } else {
        s21_specification_x_X(str, va_arg(*arg, unsigned int), 0, options);
      }
      break;
    case 'X':
      if (options->h) {
        s21_specification_x_X(
            str, (unsigned short int)va_arg(*arg, unsigned int), 1, options);
      } else if (options->l) {
        s21_specification_x_X(
            str, (unsigned long int)va_arg(*arg, unsigned long int), 1,
            options);
      } else {
        s21_specification_x_X(str, va_arg(*arg, unsigned int), 1, options);
      }
      break;
    case 'o':
      if (options->h) {
        s21_specification_o(str, (unsigned short int)va_arg(*arg, unsigned int),
                            options);
      } else if (options->l) {
        s21_specification_o(
            str, (unsigned long int)va_arg(*arg, unsigned long int), options);
      } else {
        s21_specification_o(str, va_arg(*arg, unsigned int), options);
      }
      break;
    case 'p':
      s21_specification_p(str, va_arg(*arg, void *), options);
      break;
    default:
      options->error = 1;
      break;
  }
}

void s21_check_flags_sprintf(const char flag, opt *options) {
  switch (flag) {
    case '-':
      if (options->minus || options->zero) options->error = 1;
      options->minus = 1;
      break;
    case '+':
      if (options->plus || options->space) options->error = 1;
      options->plus = 1;
      break;
    case ' ':
      if (options->plus || options->space) options->error = 1;
      options->space = 1;
      break;
    case '#':
      if (options->sign) options->error = 1;
      options->sign = 1;
      break;
    case '0':
      if (options->minus || options->zero) options->error = 1;
      options->zero = 1;
      break;
    default:
      options->error = 1;
      break;
  }
}

int s21_check_width_sprintf(const char *format, opt *options, va_list *arg) {
  char temp[1024] = {0};
  int width = 0;
  int i = 0;
  int isWrite = 0;
  int isStar = 0;
  while (s21_strchr("1234567890*", *format)) {
    if ('*' == *format) {
      if (isStar || isWrite) options->error = 1;
      options->width = va_arg(*arg, int);
      isStar = 1;
      format++;
    } else {
      if (isStar) options->error = 1;
      isWrite = 1;
      temp[i++] = *format++;
    }
  }
  for (int i = 0; temp[i] != '\0'; i++) {
    width = width * 10 + (temp[i] - '0');
  }
  if (isWrite && !options->error) {
    options->width = width;
  }
  int res = 0;
  if (isStar) {
    res = -1;
  } else {
    res = s21_strlen(temp);
  }
  return res;
}

int s21_check_precision_sprintf(const char *format, opt *options,
                                va_list *arg) {
  char temp[1024] = {0};
  int precision = 0;
  int i = 0;
  int isWrite = 0;
  int isStar = 0;
  format++;
  while (s21_strchr(".1234567890*", *format)) {
    if ('*' == *format) {
      if (isStar || isWrite) options->error = 1;
      options->precision = va_arg(*arg, int);
      isStar = 1;
      format++;
    } else if ('.' == *format) {
      options->error = 1;
    } else {
      if (isStar) options->error = 1;
      isWrite = 1;
      temp[i++] = *format++;
    }
  }
  for (int i = 0; temp[i] != '\0'; i++) {
    precision = precision * 10 + (temp[i] - '0');
  }
  if (isWrite && !options->error) {
    options->precision = precision;
  }
  int res = 0;
  if (isStar) {
    res = -1;
  } else if (!isStar && !isWrite) {
    options->precision = -1;
    res = 0;
  } else {
    res = s21_strlen(temp);
  }
  return res;
}

void s21_check_lenght_sprintf(const char flag, opt *options) {
  switch (flag) {
    case 'l':
      if (options->l || options->L || options->h) options->error = 1;
      options->l = 1;
      break;
    case 'L':
      if (options->l || options->L || options->h) options->error = 1;
      options->L = 1;
      break;
    case 'h':
      if (options->l || options->L || options->h) options->error = 1;
      options->h = 1;
      break;
    default:
      options->error = 1;
      break;
  }
}
