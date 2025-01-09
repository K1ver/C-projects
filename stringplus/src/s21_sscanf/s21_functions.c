#include "../s21_string.h"

int s21_isdigit(char c) {
  int res = 0;
  if (c >= '0' && c <= '9') {
    res = 1;
  }
  return res;
}

const char* s21_strToInt(const char* str, void* result, opt* options) {
  if (str == s21_NULL || *str == '\0') {
    options->error = 1;
  }
  long int res = 0;
  str = s21_skipSpace(str);
  int negative = 0;
  int found_digit = 0;
  if (*str == '-') {
    negative = 1;
    str++;
  } else if (*str == '+') {
    str++;
  }
  int width = options->width;
  for (; *str; str++) {
    if (!s21_isdigit(*str) || (options->width && width == 0)) {
      break;
    }
    found_digit = 1;
    res = res * 10 + (*str - '0');
    width--;
  }
  if (!found_digit) {
    options->error = 1;
  }
  if (negative) {
    res = -res;
  }

  if (options->width != -1 && !options->error) {
    if (options->h) {
      short int* p = (short int*)result;
      *p = (short int)res;
    } else if (options->l) {
      long int* p = (long int*)result;
      *p = (long int)res;
    } else {
      int* p = (int*)result;
      *p = (int)res;
    }
  }
  return str;
}

const char* s21_strToFloat(const char* str, void* result, opt* options) {
  long double res = 0;
  int negative = 0;
  int foundDigits = 0;
  char intPart[4096] = {0};
  char atfterPointPart[4096] = {0};
  str = s21_skipSpace(str);
  int i = 0;
  int width = options->width;

  if (*str == '-') {
    negative = 1;
    str++;
  } else if (*str == '+') {
    str++;
  }

  while (*str && s21_isdigit(*str)) {
    if (options->width && width == 0) {
      break;
    }
    foundDigits = 1;
    intPart[i++] = *str++;
  }
  int PartInt;
  s21_strToInt(intPart, &PartInt, options);
  res += PartInt;
  if (*str == '.') {
    foundDigits = 0;
    str++;
    i = 0;
    while (*str && s21_isdigit(*str)) {
      if (options->width && width == 0) {
        break;
      }
      foundDigits = 1;
      atfterPointPart[i++] = *str++;
    }
    long double cpyres = res;
    while (i > 0) {
      int temp = atfterPointPart[i - 1] - '0';
      int dec = (int)cpyres * 10;
      cpyres -= (int)cpyres;
      cpyres += dec + temp;
      cpyres /= 10;
      i--;
    }
    res = cpyres;
  }

  if (!foundDigits) {
    options->error = 1;
  }
  if (negative) {
    res = -res;
  }
  if (options->width != -1 && !options->error) {
    if (options->L) {
      long double* p = (long double*)result;
      *p = (long double)res;
    } else if (options->l) {
      double* p = (double*)result;
      *p = (double)res;
    } else {
      float* p = (float*)result;
      *p = (float)res;
    }
  }

  return str;
}

const char* s21_strToUnsignedInt(const char* str, void* result, opt* options) {
  if (str == s21_NULL || *str == '\0') {
    options->error = 1;
  }
  long long int res = 0;
  str = s21_skipSpace(str);
  int negative = 0;
  int found_digit = 0;

  if (*str == '-') {
    negative = 1;
    str++;
  } else if (*str == '+') {
    str++;
  }
  int width = options->width;
  for (; *str; str++) {
    if (!s21_isdigit(*str) || (options->width && width == 0)) {
      break;
    }
    found_digit = 1;
    res = res * 10 + (*str - '0');
    width--;
  }
  if (!found_digit) {
    options->error = 1;
  }
  if (negative) {
    res = -res;
  }

  if (options->width != -1 && !options->error) {
    if (options->h) {
      unsigned short int* p = (unsigned short int*)result;
      *p = (unsigned short int)res;
    } else if (options->l) {
      unsigned long int* p = (unsigned long int*)result;
      *p = (unsigned long int)res;
    } else {
      unsigned int* p = (unsigned int*)result;
      *p = (unsigned int)res;
    }
  }
  return str;
}

const char* s21_strToHex(const char* str, void* result, opt* options) {
  if (str == s21_NULL || *str == '\0') {
    options->error = 1;
  }
  str = s21_skipSpace(str);
  char temp[4096] = {0};
  int width = options->width;
  int i = 0;
  while ((*str && *str != ' ' && *str != '\n' && *str != '\t') &&
         (options->width == 0 || (options->width != 0 && width != 0))) {
    if (options->width == -1) {
      str++;
    } else {
      temp[i++] = *str++;
    }
  }
  while (((temp[i - 1] >= 'G' && temp[i - 1] <= 'Z') ||
          (temp[i - 1] >= 'g' && temp[i - 1] <= 'z')) &&
         !s21_isdigit(temp[i - 1])) {
    options->error = 1;
    i--;
  }
  i = 0;
  while (s21_isdigit(temp[i])) {
    i++;
  }
  while ((temp[i] >= 'A' && temp[i] <= 'F') ||
         (temp[i] >= 'a' && temp[i] <= 'f')) {
    i++;
  }
  long long int hex = 0;
  int base = 1;
  while (!s21_isdigit(temp[i - 1])) {
    int tempI = 1;
    if ((temp[i - 1] >= 'A' && temp[i - 1] <= 'F')) {
      tempI = tempI * 10 + temp[i - 1] - 'A';
    } else if ((temp[i - 1] >= 'a' && temp[i - 1] <= 'f')) {
      tempI = tempI * 10 + temp[i - 1] - 'a';
    }
    hex = hex + (tempI * base);
    base *= 16;
    i--;
  }
  while (i > 0) {
    int lastdigit = temp[i - 1] - '0';

    hex += lastdigit * base;
    base = base * 16;
    i--;
  }
  if (options->width != -1 && !options->error) {
    if (options->h) {
      unsigned short int* p = (unsigned short int*)result;
      *p = (unsigned short int)hex;
    } else if (options->l) {
      unsigned long int* p = (unsigned long int*)result;
      *p = (unsigned long int)hex;
    } else {
      unsigned int* p = (unsigned int*)result;
      *p = (unsigned int)hex;
    }
  }
  return str;
}

const char* s21_strToOctal(const char* str, void* result, opt* options) {
  if (str == s21_NULL || *str == '\0') {
    options->error = 1;
  }
  long long int res = 0;
  str = s21_skipSpace(str);
  int negative = 0;
  int found_digit = 0;

  if (*str == '-') {
    negative = 1;
    str++;
  } else if (*str == '+') {
    str++;
  }
  int width = options->width;
  for (; *str; str++) {
    if (!s21_isdigit(*str) || (options->width && width == 0)) {
      break;
    }
    found_digit = 1;
    res = res * 10 + (*str - '0');
    width--;
  }
  if (!found_digit) {
    options->error = 1;
  }
  if (negative) {
    res = -res;
  }

  int base = 1;
  int octal = 0;

  while (res) {
    int lastdigit = res % 10;

    res = res / 10;

    octal += lastdigit * base;

    base = base * 8;
  }
  res = octal;
  if (options->width != -1 && !options->error) {
    if (options->h) {
      unsigned short int* p = (unsigned short int*)result;
      *p = (unsigned short int)res;
    } else if (options->l) {
      unsigned long int* p = (unsigned long int*)result;
      *p = (unsigned long int)res;
    } else {
      unsigned int* p = (unsigned int*)result;
      *p = (unsigned int)res;
    }
  }
  return str;
}
const char* s21_strToChar(const char* str, char* result, opt* options) {
  if (*str == '\0') {
    options->error = 1;
  }
  *result = *str;
  return ++str;
}

const char* s21_strToStr(const char* str, char* result, opt* options) {
  str = s21_skipSpace(str);
  int width = options->width;
  s21_size_t i = 0;
  while ((*str && *str != ' ' && *str != '\n' && *str != '\t') &&
         (options->width == 0 || (options->width != 0 && width != 0))) {
    if (options->width == -1) {
      str++;
    } else {
      result[i++] = *str++;
    }
    width--;
  }
  return str;
}

const char* s21_skipSpace(const char* str) {
  while (*str == ' ') {
    str++;
  }
  return str;
}