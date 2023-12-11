#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  *result = simple_floor(value);
  return 0;
}

/// @brief Округляет Decimal до ближайшего целого числа.
/// @param src входное значение структуры децимала
/// @param dst выходное ссылка на структуру в котторую записывается результат
/// @return 0 - если все ок 1 - если все плохо
int s21_round(s21_decimal value, s21_decimal *result) {
  s21_big_decimal big_dec_res = {0};
  s21_big_decimal big_dec = {0};
  if (get_exp(value.bits[3])) {
    *result = reduce_exp_dec(value, 1);
    value = reduce_exp_dec(value, 0);
    big_dec_res = decimal_to_big(value);
    big_dec = decimal_to_big(*result);
    big_dec = simple_mod(big_dec, bdec_ten);
    if (big_dec.bits[0] >= 5) big_dec_res = simple_add(big_dec_res, bdec_one);
    big_to_dec(&big_dec_res, result);
  } else
    *result = value;
  return 0;
}

/// @brief Возвращает целые цифры указанного Decimal числа;
/// любые дробные цифры отбрасываются, включая конечные нули.
/// @param value округляемое число
/// @param result указатель на результат
/// @return 0 - если все ок 1 - если все плохо
int s21_truncate(s21_decimal value, s21_decimal *result) {
  *result = reduce_exp_dec(value, 0);
  return 0;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  for (int i = 0; i < 3; i++) {
    result->bits[i] = value.bits[i];
  }
  int exp = get_exp(value.bits[3]);
  set_exp(&result->bits[3], exp);
  int znak = get_sign(value.bits[3]);
  if (znak == 0) {
    set_sign(&result->bits[3], 1);
  } else {
    set_sign(&result->bits[3], 0);
  }
  return 0;
}
