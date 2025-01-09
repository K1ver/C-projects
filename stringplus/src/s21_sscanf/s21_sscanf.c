#include "../s21_string.h"

int s21_sscanf(const char *str, const char *format, ...) {
  va_list(args);
  va_start(args, format);
  s21_parser_sscanff(str, format, &args);
  va_end(args);
  return s21_strlen(str);
}

// %[*][ширина][длина]спецификатор.
void s21_parser_sscanff(const char *str, const char *format, va_list *args) {
  while (*format && *str) {
    if (*format == *str && *format != '%') {
      format++;
      str++;
    } else {
      format++;
      opt options = {0};
      if (s21_strchr("1234567890*", *format) && !options.error) {
        int count = s21_check_width_sscanf(format, &options);
        if (!options.error) {
          if (count == -1) {
            format++;
          } else {
            format += count;
          }
        }
      }
      while (s21_strchr("hlL", *format) && !options.error) {
        s21_check_lenght_sscanf(*format++, &options);
      }
      if (!options.error) {
        str = s21_check_specification_sscanf(str, *format++, &options, args);
      }
      if (options.error) {
        break;
      }
    }
  }
}

const char *s21_check_specification_sscanf(const char *str,
                                           const char specification,
                                           opt *options, va_list *arg) {
  switch (specification) {
    case 'c':
      if (options->width != -1) {
        str = s21_strToChar(str, va_arg(*arg, char *), options);
      } else {
        char c = '0';
        str = s21_strToChar(str, &c, options);
      }
      break;
    case 'd':
      if (options->width != -1) {
        if (options->l) {
          str = s21_strToInt(str, va_arg(*arg, long int *), options);
        } else if (options->h) {
          str = s21_strToInt(str, va_arg(*arg, short int *), options);
        } else {
          str = s21_strToInt(str, va_arg(*arg, int *), options);
        }
      } else {
        str = s21_strToInt(str, 0, options);
      }
      break;
    case 'f':
      if (options->width != -1) {
        if (options->l) {
          str = s21_strToFloat(str, va_arg(*arg, double *), options);
        } else if (options->L) {
          str = s21_strToFloat(str, va_arg(*arg, long double *), options);
        } else {
          str = s21_strToFloat(str, va_arg(*arg, float *), options);
        }
      } else {
        str = s21_strToFloat(str, 0, options);
      }
      break;
    case 's':
      if (options->width != -1) {
        str = s21_strToStr(str, va_arg(*arg, char *), options);
      } else {
        char s[1] = {0};
        str = s21_strToStr(str, s, options);
      }
      break;
    case 'u':
      if (options->width != -1) {
        if (options->l) {
          str = s21_strToUnsignedInt(str, va_arg(*arg, unsigned long int *),
                                     options);
        } else if (options->h) {
          str = s21_strToUnsignedInt(str, va_arg(*arg, unsigned short int *),
                                     options);
        } else {
          str =
              s21_strToUnsignedInt(str, va_arg(*arg, unsigned int *), options);
        }
      } else {
        str = s21_strToUnsignedInt(str, 0, options);
      }
      break;
    case 'g':
      if (options->width != -1) {
        if (options->l) {
          str = s21_strToFloat(str, va_arg(*arg, double *), options);
        } else if (options->L) {
          str = s21_strToFloat(str, va_arg(*arg, long double *), options);
        } else {
          str = s21_strToFloat(str, va_arg(*arg, float *), options);
        }
      } else {
        str = s21_strToFloat(str, 0, options);
      }
      break;
    case 'G':
      if (options->width != -1) {
        if (options->l) {
          str = s21_strToFloat(str, va_arg(*arg, double *), options);
        } else if (options->L) {
          str = s21_strToFloat(str, va_arg(*arg, long double *), options);
        } else {
          str = s21_strToFloat(str, va_arg(*arg, float *), options);
        }
      } else {
        str = s21_strToFloat(str, 0, options);
      }
      break;
    case 'e':
      if (options->width != -1) {
        if (options->l) {
          str = s21_strToFloat(str, va_arg(*arg, double *), options);
        } else if (options->L) {
          str = s21_strToFloat(str, va_arg(*arg, long double *), options);
        } else {
          str = s21_strToFloat(str, va_arg(*arg, float *), options);
        }
      } else {
        str = s21_strToFloat(str, 0, options);
      }
      break;
    case 'E':
      if (options->width != -1) {
        if (options->l) {
          str = s21_strToFloat(str, va_arg(*arg, double *), options);
        } else if (options->L) {
          str = s21_strToFloat(str, va_arg(*arg, long double *), options);
        } else {
          str = s21_strToFloat(str, va_arg(*arg, float *), options);
        }
      } else {
        str = s21_strToFloat(str, 0, options);
      }
      break;
    case 'x':
      if (options->width != -1) {
        if (options->l) {
          str = s21_strToHex(str, va_arg(*arg, unsigned long int *), options);
        } else if (options->h) {
          str = s21_strToHex(str, va_arg(*arg, unsigned short int *), options);
        } else {
          str = s21_strToHex(str, va_arg(*arg, unsigned int *), options);
        }
      } else {
        str = s21_strToHex(str, 0, options);
      }
      break;
    case 'X':
      if (options->width != -1) {
        if (options->l) {
          str = s21_strToHex(str, va_arg(*arg, unsigned long int *), options);
        } else if (options->h) {
          str = s21_strToHex(str, va_arg(*arg, unsigned short int *), options);
        } else {
          str = s21_strToHex(str, va_arg(*arg, unsigned int *), options);
        }
      } else {
        str = s21_strToHex(str, 0, options);
      }
      break;
    case 'o':
      if (options->width != -1) {
        if (options->l) {
          str = s21_strToOctal(str, va_arg(*arg, unsigned long int *), options);
        } else if (options->h) {
          str =
              s21_strToOctal(str, va_arg(*arg, unsigned short int *), options);
        } else {
          str = s21_strToOctal(str, va_arg(*arg, unsigned int *), options);
        }
      } else {
        str = s21_strToOctal(str, 0, options);
      }
      break;
    case 'p':

      break;
    default:
      options->error = 1;
      break;
  }
  return str;
}

int s21_check_width_sscanf(const char *format, opt *options) {
  char temp[1024] = {0};
  int width = 0;
  int i = 0;
  int isWrite = 0;
  int isStar = 0;
  while (s21_strchr("1234567890*", *format)) {
    if ('*' == *format) {
      if (isStar || isWrite) options->error = 1;
      options->width = -1;
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

void s21_check_lenght_sscanf(const char flag, opt *options) {
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
