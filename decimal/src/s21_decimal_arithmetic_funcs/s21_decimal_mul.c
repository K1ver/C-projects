#include "../s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal lvalue_1, lvalue_2;
  s21_copy_decimal(value_1, &lvalue_1);
  s21_copy_decimal(value_2, &lvalue_2);
  s21_set_zero(result);

  s21_equalize_scale(&lvalue_1, &lvalue_2);

  int sign_1 = s21_get_sign(lvalue_1);
  int sign_2 = s21_get_sign(lvalue_2);
  int error = 0;
  error = s21_mull_with_sign(lvalue_1, lvalue_2, result);
  if ((sign_1 && sign_2) || (!sign_1 && !sign_2)) {
    s21_set_sign(result, 0);
  } else {
    s21_set_sign(result, 1);
  }
  if (error == 1) {
    if (s21_get_sign(*result)) {
      error = 2;
    }
    s21_set_sign(result, 0);
  }
  if (s21_is_zero(lvalue_1) || s21_is_zero(lvalue_2)) {
    s21_set_sign(result, 0);
  }
  s21_set_scale(result, s21_get_scale(value_1) + s21_get_scale(value_2));
  return error;
}

int s21_mull_with_sign(s21_decimal lvalue_1, s21_decimal lvalue_2,
                       s21_decimal *result) {
  unsigned long carry = 0;
  int error = 0;
  s21_decimal one = {{1, 0, 0, 0}};
  s21_decimal neg_one = {{1, 0, 0, SIGN_MASK}};
  if (s21_is_max_dec(lvalue_1) &&
      (s21_is_greater_or_equal(lvalue_2, one) ||
       s21_is_less_or_equal(lvalue_2, neg_one) || !s21_is_zero(lvalue_2))) {
    error = 1;
  } else if (s21_is_max_dec(lvalue_2) &&
             (s21_is_greater_or_equal(lvalue_1, one) ||
              s21_is_less_or_equal(lvalue_1, neg_one) ||
              !s21_is_zero(lvalue_1))) {
    error = 1;
  } else {
    if (carry) error = 1;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (s21_as_uint(lvalue_2.bits[i])) {
          unsigned long val1 = s21_as_uint(lvalue_1.bits[j]);
          unsigned long val2 = s21_as_uint(lvalue_2.bits[i]);
          carry += val1 * val2;
          result->bits[j] = s21_as_int(carry);
          carry >>= 32;
        }
      }
    }
  }

  return error;
}