#ifndef S21_STRING
#define S21_STRING

#include <math.h>
#include <stdarg.h>
#include <stdlib.h>

typedef struct options {
  int minus, plus, space, sign, zero, width, precision, h, l, L, error;
} opt;

#define s21_NULL (void *)0
#define s21_size_t unsigned long int

void *s21_to_upper(const char *str);
s21_size_t s21_strlen(const char *str);
char *s21_strtok(char *str, const char *delim);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
char *s21_strstr(const char *haystack, const char *needle);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strpbrk(const char *str1, const char *str2);
void *s21_to_lower(const char *str);
void *s21_to_upper(const char *str);
void *s21_trim(const char *src, const char *trim_chars);
char *s21_strerror(int errnum);
char *s21_strrchr(const char *str, s21_size_t c);
void *s21_memchr(const void *str, int c, s21_size_t n);
char *s21_strchr(const char *str, int c);
int s21_sprintf(char *str, const char *format, ...);
int s21_sscanf(const char *str, const char *format, ...);
void s21_specification_c(char *str, int c, opt *options);
void s21_specification_x_X(char *str, unsigned long long int d, int isUp,
                           opt *options);
void s21_specification_p(char *str, void *p, opt *options);
void s21_specification_d_u(long long int d, char *str, opt *options, int isU);
void s21_specification_s(char *str, const char *value, opt *options);
void s21_specification_o(char *str, unsigned long long int d, opt *options);
void s21_specification_e(long double floatNumber, char *floatBuffer,
                         opt *options, int isUp);
int s21_itoa(int x, char str[], int d);
void s21_specification_f(char *baseStr, long double n, opt *options);
void s21_precision_o(char *o, opt *options);
void s21_add_zero_x_X(char *hex, int param, int isUp, opt *options);
void s21_add_zero_d_u(char *d, int param, opt *options, int isNeg, int isU);
void s21_parser_sprintf(char *str, const char *format, va_list *args);
void s21_add_char(char *str, char c);
void s21_check_flags_sprintf(const char flag, opt *options);
int s21_check_width_sprintf(const char *format, opt *options, va_list *arg);
int s21_check_precision_sprintf(const char *format, opt *options, va_list *arg);
void s21_check_lenght_sprintf(const char flag, opt *options);
void s21_check_specification_sprintf(char *str, const char specification,
                                     opt *options, va_list *arg);
void s21_decimalToOctal(char *o, unsigned long long int d);
void s21_decimalToHexadecimal(char *hex, unsigned long long int d, int isUp);
int s21_intToStr(long long int d, char *str);
void s21_reverseString(char *string, int length);
void s21_reverse(char *str, int len);
void s21_del_char_p(char *buff);
void s21_floatingPointToStr(char *res, long double fpart, int afterpoint);
int s21_floatDecimalToStr(unsigned long long int x, char *str, int d);
void s21_ftoa(long double n, char *res, opt *options);
void s21_parser_sscanff(const char *str, const char *format, va_list *args);
const char *s21_check_specification_sscanf(const char *str,
                                           const char specification,
                                           opt *options, va_list *arg);
int s21_check_width_sscanf(const char *format, opt *options);
void s21_check_lenght_sscanf(const char flag, opt *options);
const char *s21_strToInt(const char *str, void *result, opt *options);
const char *s21_strToUnsignedInt(const char *str, void *result, opt *options);
const char *s21_strToOctal(const char *str, void *result, opt *options);
const char *s21_strToHex(const char *str, void *result, opt *options);
const char *s21_strToFloat(const char *str, void *result, opt *options);
const char *s21_strToChar(const char *str, char *result, opt *options);
const char *s21_strToStr(const char *str, char *result, opt *options);
const char *s21_skipSpace(const char *str);
int s21_isdigit(char c);

#endif
