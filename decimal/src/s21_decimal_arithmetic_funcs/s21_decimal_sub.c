#include "../s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal lvalue_1, lvalue_2;
  s21_copy_decimal(value_1, &lvalue_1);
  s21_copy_decimal(value_2, &lvalue_2);
  s21_set_zero(result);

  s21_equalize_scale(&lvalue_1, &lvalue_2);

  int sign_1 = s21_get_sign(lvalue_1);
  int sign_2 = s21_get_sign(lvalue_2);
  int error = 0;
  if (!s21_is_zero(lvalue_1) || !s21_is_zero(lvalue_2)) {
    if (sign_1 == sign_2) {
      if (sign_1 && sign_1) {
        s21_set_sign(&lvalue_2, 0);
      } else {
        s21_set_sign(&lvalue_2, 1);
      }
      error = s21_add(lvalue_1, lvalue_2, result);
    } else {
      int cmp_abs = s21_compare_abs(lvalue_1, lvalue_2);
      if (cmp_abs >= 0) {
        error = s21_add_same_sign(lvalue_1, lvalue_2, result);
      } else {
        error = s21_add_same_sign(lvalue_2, lvalue_1, result);
      }
      if (!sign_1 && sign_2) {
        s21_set_sign(result, 0);
      } else {
        s21_set_sign(result, 1);
      }
    }
  }

  s21_set_scale(result, s21_get_scale(lvalue_1));
  return error;
}

int s21_sub_same_sign(s21_decimal lvalue_1, s21_decimal lvalue_2,
                      s21_decimal *result) {
  unsigned long borrow = 0;
  int error = 0;
  int sign = 0;
  for (int i = 0; i < 3; i++) {
    borrow = s21_as_uint(lvalue_1.bits[i]) - s21_as_uint(lvalue_2.bits[i]);
    if ((long int)borrow < 0) {
      sign = 1;
      result->bits[i] = s21_as_int(borrow);
      result->bits[i] *= -1;
    } else {
      result->bits[i] = s21_as_int(borrow);
    }
    borrow >>= 32;
  }
  if (borrow) error = 2;
  s21_set_sign(result, sign);

  return error;
}