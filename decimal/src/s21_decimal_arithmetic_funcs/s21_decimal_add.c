#include "../s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal lvalue_1, lvalue_2;
  s21_copy_decimal(value_1, &lvalue_1);
  s21_copy_decimal(value_2, &lvalue_2);
  s21_set_zero(result);

  s21_equalize_scale(&lvalue_1, &lvalue_2);
  int sign_1 = s21_get_sign(lvalue_1);
  int sign_2 = s21_get_sign(lvalue_2);
  int error = 0;
  if (sign_1 == sign_2) {
    error = s21_add_same_sign(lvalue_1, lvalue_2, result);
    s21_set_sign(result, sign_1);
  } else {
    if (s21_compare_abs(lvalue_1, lvalue_2) >= 0) {
      error = s21_sub_same_sign(lvalue_1, lvalue_2, result);
      s21_set_sign(result, sign_1);
    } else {
      error = s21_sub_same_sign(lvalue_2, lvalue_1, result);
      s21_set_sign(result, sign_2);
    }
    if (s21_is_zero(*result)) {
      s21_set_sign(result, 0);
    }
  }
  s21_set_scale(result, s21_get_scale(lvalue_1));
  return error;
}

int s21_add_same_sign(s21_decimal lvalue_1, s21_decimal lvalue_2,
                      s21_decimal *result) {
  unsigned long carry = 0;
  int error = 0;
  for (int i = 0; i < 3; i++) {
    unsigned long val1 = s21_as_uint(lvalue_1.bits[i]);
    unsigned long val2 = s21_as_uint(lvalue_2.bits[i]);
    carry += val1 + val2;
    result->bits[i] = s21_as_int(carry);
    carry >>= 32;
  }
  if (carry) error = 1;

  return error;
}