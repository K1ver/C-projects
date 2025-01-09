#ifndef S21_DECIMAL
#define S21_DECIMAL

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define SCALE_MASK 0x00FF0000
#define SIGN_MASK 0x80000000
#define S21_2IN32 4294967296
#define s21_MAXDEC 2e96 - 1

typedef struct {
  int bits[4];
} s21_decimal;

typedef union {
  int ui;
  float fl;
} floatbits;

// arithmetic
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
// Converter
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
// compare
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
// another_func
int s21_negate(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
// help_func
int s21_is_zero(s21_decimal value);
unsigned int s21_as_uint(int x);
int s21_as_int(unsigned int x);
int s21_drop_last_digit(s21_decimal *src);
void s21_copy_decimal(s21_decimal value_1, s21_decimal *value_2);
int s21_sub_same_sign(s21_decimal lvalue_1, s21_decimal lvalue_2,
                      s21_decimal *result);
int s21_add_same_sign(s21_decimal lvalue_1, s21_decimal lvalue_2,
                      s21_decimal *result);
int s21_mull_with_sign(s21_decimal value_1, s21_decimal value_2,
                       s21_decimal *result);
void s21_equalize_scale(s21_decimal *value_1, s21_decimal *value_2);
void s21_increase_scale(s21_decimal *value);
int s21_compare_abs(s21_decimal value_1, s21_decimal value_2);
int s21_compare_with_minus(s21_decimal value_1, s21_decimal value_2);
void s21_set_zero(s21_decimal *value);
void s21_set_sign(s21_decimal *value, int sign);
void s21_set_scale(s21_decimal *value, int scale);
int s21_get_sign(s21_decimal value);
int s21_get_scale(s21_decimal value);
int s21_is_max_dec(s21_decimal value);
void s21_set_bit(s21_decimal *dst, int index, int bit);
int getFloatSign(float *src);
int getFloatExp(float *src);
int s21_get_bit(s21_decimal num, int curBit);

#endif