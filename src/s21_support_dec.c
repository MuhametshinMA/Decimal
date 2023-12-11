#include <stdio.h>

#include "s21_decimal.h"

void set_exp(unsigned int *dec, unsigned char exp) { *dec = exp << 16; }

void set_bit(unsigned int *num, unsigned char bit_num) {
  *num |= (unsigned char)1 << bit_num;
}

void reset_bit(unsigned int *num, unsigned char bit_num) {
  *num &= ~((unsigned char)1 << bit_num);
}

char get_exp(unsigned int dec) {
  unsigned int exp = 0;
  for (unsigned char i = 16; i < 24; i++) {
    if (dec & (unsigned char)1 << i) {
      set_bit(&exp, i - 16);
    }
  }
  return exp;
}

char check_bit(unsigned int num, unsigned char index) {
  char bit = 0;
  if (index < 32) {
    if ((num & (unsigned int)1 << index) != 0) {
      bit = 1;
    } else {
      bit = 0;
    }
  } else {
    bit = -1;
  }
  return bit;
}

unsigned char gen_rand_exp() { return rand() % 29; }

unsigned char gen_rand_sign() { return (rand() % 11) > 5 ? 1 : 0; }

char get_sign(unsigned int dec) { return check_bit(dec, 31); }

void set_sign(unsigned int *dec, char sign) {
  sign ? set_bit(dec, 31) : reset_bit(dec, 31);
}

s21_big_decimal decimal_to_big(s21_decimal dec) {
  s21_big_decimal big_dec = {0};
  big_dec.bits[0] = dec.bits[0];
  big_dec.bits[1] = dec.bits[1];
  big_dec.bits[2] = dec.bits[2];
  big_dec.mantice = dec.bits[3];
  return big_dec;
}

s21_decimal set_rand_decimal() {
  s21_decimal dec = {0};
  dec.bits[0] = rand();
  dec.bits[1] = rand();
  dec.bits[2] = rand();
  set_exp(&dec.bits[3], gen_rand_exp());
  set_sign(&dec.bits[3], gen_rand_sign());
  return dec;
}

s21_decimal set_decimal(unsigned int low_bit, unsigned int mid_bit,
                        unsigned int high_bit, unsigned char exp,
                        unsigned char sign) {
  s21_decimal dec = {0};
  dec.bits[0] = low_bit;
  dec.bits[1] = mid_bit;
  dec.bits[2] = high_bit;
  set_exp(&dec.bits[3], exp);
  set_sign(&dec.bits[3], sign);
  return dec;
}

void shift_bigdec_to_high(s21_big_decimal *bdec) {
  for (char i = 5; i >= 0; i--) {
    if (check_bit(bdec->bits[(unsigned char)i], 31)) {
      set_bit(&(bdec->bits[(unsigned char)i + 1]), 0);
    }
    bdec->bits[(unsigned char)i] =
        singl_high_shift(bdec->bits[(unsigned char)i]);
  }
}

unsigned int singl_high_shift(unsigned int num) { return num <<= 1; }

unsigned int singl_low_shift(unsigned int num) { return num >>= 1; }

unsigned char is_empty_bdec(s21_big_decimal bdec) {
  return bdec.bits[5] || bdec.bits[4] || bdec.bits[3] || bdec.bits[2] ||
                 bdec.bits[1] || bdec.bits[0]
             ? 0
             : 1;
}

int is_empty_dec(s21_decimal dec) {
  return dec.bits[2] || dec.bits[1] || dec.bits[0] ? 0 : 1;
}

unsigned char shift_bigdec_to_low(s21_big_decimal *bdec) {
  unsigned char was_shifted = 0;
  if (!is_empty_bdec(*bdec)) {
    for (char i = 0; i < 6; i++) {
      bdec->bits[(unsigned char)i] =
          singl_low_shift(bdec->bits[(unsigned char)i]);
      if (check_bit(bdec->bits[(unsigned char)i + 1], 0)) {
        set_bit(&(bdec->bits[(unsigned char)i]), 31);
      }
      was_shifted = 1;
    }
  }

  return was_shifted;
}

char *print_dec(s21_decimal dec) {
  char *str = calloc(256, sizeof(char));
  sprintf(str, "%hhd %hhu %u %u %u\n", get_sign(dec.bits[3]),
          get_exp(dec.bits[3]), dec.bits[2], dec.bits[1], dec.bits[0]);
  return str;
}

// simple arithmetic

/// @brief Исключающее ИЛИ
/// @param big_value_1
/// @param big_value_2
/// @return s21_big_decimal
s21_big_decimal exclusive_or(s21_big_decimal big_value_1,
                             s21_big_decimal big_value_2) {
  for (int i = 0; i < INT_BIG_DECIMAL; i++) {
    big_value_1.bits[i] = big_value_1.bits[i] ^ big_value_2.bits[i];
  }

  return big_value_1;
}

/// @brief Логическое И
/// @param big_value_1
/// @param big_value_2
/// @return s21_big_decimal
s21_big_decimal bit_and(s21_big_decimal big_value_1,
                        s21_big_decimal big_value_2) {
  s21_big_decimal big_rezult = {0};
  for (int i = 0; i < INT_BIG_DECIMAL; i++) {
    big_rezult.bits[i] = big_value_1.bits[i] & big_value_2.bits[i];
  }
  return big_rezult;
}

s21_big_decimal negative(s21_big_decimal big_value_1) {
  for (int i = 0; i < INT_BIG_DECIMAL; i++) {
    big_value_1.bits[i] = ~big_value_1.bits[i];
  }
  s21_big_decimal big_value_2 = {0};
  big_value_2.bits[0] = 1;

  big_value_1 = simple_add(big_value_1, big_value_2);

  return big_value_1;
}

s21_big_decimal simple_add(s21_big_decimal big_value_1,
                           s21_big_decimal big_value_2) {
  s21_big_decimal big_rezult = {0};

  big_rezult = exclusive_or(big_value_1, big_value_2);
  big_value_1 = bit_and(big_value_1, big_value_2);
  shift_bigdec_to_high(&big_value_1);

  while (DEC1_ZERO) {
    big_value_2 = big_rezult;
    big_rezult = exclusive_or(big_rezult, big_value_1);
    big_value_1 = bit_and(big_value_2, big_value_1);
    shift_bigdec_to_high(&big_value_1);
  }

  return big_rezult;
}

void full_add(s21_big_decimal big_value_1, s21_big_decimal big_value_2,
              s21_big_decimal *big_rezult) {
  unsigned char sign1 = get_sign(big_value_1.mantice);
  unsigned char sign2 = get_sign(big_value_2.mantice);

  set_sign(&big_value_1.mantice, 0);
  set_sign(&big_value_2.mantice, 0);

  if (sign1 ^ sign2) {
    if (s21_is_big_less(big_value_1, big_value_2))
      *big_rezult = simple_sub(big_value_2, big_value_1);
    else
      *big_rezult = simple_sub(big_value_1, big_value_2);
  } else {
    *big_rezult = simple_add(big_value_1, big_value_2);
  }

  if (s21_is_big_less(big_value_1, big_value_2) && sign2) {
    set_sign(&big_rezult->mantice, 1);
  } else if (s21_is_big_less(big_value_2, big_value_1) && sign1) {
    set_sign(&big_rezult->mantice, 1);
  }
}

s21_big_decimal simple_sub(s21_big_decimal big_value_1,
                           s21_big_decimal big_value_2) {
  s21_big_decimal big_rezult = {0};
  big_rezult = simple_add(big_value_1, negative(big_value_2));
  reset_bit(&big_rezult.bits[5], 31);
  return big_rezult;
}

void full_sub(s21_big_decimal big_value_1, s21_big_decimal big_value_2,
              s21_big_decimal *big_rezult) {
  unsigned char sign1 = get_sign(big_value_1.mantice);
  unsigned char sign2 = get_sign(big_value_2.mantice);

  set_sign(&big_value_1.mantice, 0);
  set_sign(&big_value_2.mantice, 0);

  if (sign1 ^ sign2) {
    *big_rezult = simple_add(big_value_1, big_value_2);
  } else {
    if (s21_is_big_less(big_value_1, big_value_2))
      *big_rezult = simple_sub(big_value_2, big_value_1);
    else
      *big_rezult = simple_sub(big_value_1, big_value_2);
  }

  if (s21_is_big_less(big_value_1, big_value_2)) {
    if (sign2)
      set_sign(&big_rezult->mantice, 0);
    else
      set_sign(&big_rezult->mantice, 1);
  } else if (s21_is_big_less(big_value_2, big_value_1)) {
    if (sign1)
      set_sign(&big_rezult->mantice, 1);
    else
      set_sign(&big_rezult->mantice, 0);
  }
}

s21_big_decimal simple_mul(s21_big_decimal big_value_1,
                           s21_big_decimal big_value_2) {
  s21_big_decimal big_rezult = {0};
  while (DEC2_ZERO) {
    if ((big_value_2.bits[0] & 0x1) == 0x1)
      big_rezult = simple_add(big_value_1, big_rezult);

    shift_bigdec_to_low(&big_value_2);
    shift_bigdec_to_high(&big_value_1);
  }

  set_sign(&big_rezult.mantice, sign_def(big_value_1, big_value_2));
  return big_rezult;
}

s21_big_decimal simple_div(s21_big_decimal big_value_1,
                           s21_big_decimal big_value_2) {
  s21_big_decimal temp_big_1 = {0};
  temp_big_1 = big_value_1;

  s21_big_decimal rez_exp = {0};
  s21_big_decimal rez = {0};

  while (s21_is_big_to_equals(temp_big_1, big_value_2)) {
    s21_big_decimal temp_divider = {0};
    temp_divider = big_value_2;
    unsigned char ten_exp = 0;
    ten_exp = mul_to_exp(temp_big_1, &temp_divider);
    s21_big_decimal bten_exp = {0};
    bten_exp.bits[0] = 1;

    for (unsigned char i = 0; i < ten_exp - 1; i++) {
      bten_exp = simple_mul(bten_exp, bdec_ten);
    }

    unsigned char sum_to_div = 0;
    sum_to_div = sum_to_divided(&temp_big_1, &temp_divider);

    s21_big_decimal bsum_div = {0};
    bsum_div.bits[0] = sum_to_div;
    rez_exp = simple_mul(bten_exp, bsum_div);

    rez = simple_add(rez, rez_exp);
  }
  return rez;
}

s21_big_decimal full_div(s21_big_decimal big_value_1,
                         s21_big_decimal big_value_2) {
  s21_big_decimal big_rezult = {0};
  s21_big_decimal big_rezult_mod = {0};
  s21_big_decimal one = {0};
  one.bits[0] = 1;

  big_rezult = simple_div(big_value_1, big_value_2);
  big_rezult_mod = simple_mod(big_value_1, big_value_2);

  unsigned char mul = 30 - mul_to_exp(big_rezult, &one);
  if (mul == 30) mul--;

  unsigned char exp = 0;

  while (big_rezult_mod.bits[0] != 0 && mul != 0) {
    mul--;
    exp++;

    big_value_1 = simple_mul(big_rezult_mod, bdec_ten);
    big_rezult = simple_mul(big_rezult, bdec_ten);
    big_rezult = simple_add(big_rezult, simple_div(big_value_1, big_value_2));
    big_rezult_mod = simple_mod(big_value_1, big_value_2);
  }

  set_exp(&big_rezult.mantice, exp);

  set_sign(&big_rezult.mantice, sign_def(big_value_1, big_value_2));
  return big_rezult;
}

unsigned char sign_def(s21_big_decimal big_value_1,
                       s21_big_decimal big_value_2) {
  return (get_sign(big_value_1.mantice) ^ get_sign(big_value_2.mantice));
}

s21_big_decimal simple_mod(s21_big_decimal big_value_1,
                           s21_big_decimal big_value_2) {
  s21_big_decimal big_rezult = {0};
  s21_big_decimal mod = {0};

  mod = simple_div(big_value_1, big_value_2);

  s21_big_decimal mul_tmp = {0};
  mul_tmp = simple_mul(mod, big_value_2);
  big_rezult = simple_sub(big_value_1, mul_tmp);

  return big_rezult;
}

unsigned char sum_to_divided(s21_big_decimal *temp_big_1,
                             s21_big_decimal *temp_divider) {
  unsigned char count_sub = 0;
  while (s21_is_big_to_equals(*temp_big_1, *temp_divider)) {
    *temp_big_1 = simple_sub(*temp_big_1, *temp_divider);
    count_sub++;
  }
  return count_sub;
}

unsigned char mul_to_exp(s21_big_decimal temp_big_1,
                         s21_big_decimal *temp_divider) {
  set_sign(&temp_big_1.mantice, 0);
  unsigned char ten_exp = 0;

  s21_big_decimal divider = {0};
  char was_in_if = 0;

  if (s21_is_big_to_equals(temp_big_1, simple_mul(*temp_divider, bdec_ten))) {
    while (s21_is_big_to_equals(temp_big_1, *temp_divider)) {
      ten_exp++;
      *temp_divider = simple_mul(*temp_divider, bdec_ten);
      if (s21_is_big_to_equals(temp_big_1, *temp_divider)) {
        was_in_if = 1;
        divider = *temp_divider;
      }
    }
    if (was_in_if) {
      *temp_divider = divider;
    }
  }
  return ten_exp;
}

// simple arithmetic

void normalize_big_dec(s21_big_decimal *big_value_1,
                       s21_big_decimal *big_value_2) {
  if (get_exp(big_value_1->mantice) > get_exp(big_value_2->mantice)) {
    cast_by_exp(big_value_2, get_exp(big_value_1->mantice));
  } else {
    cast_by_exp(big_value_1, get_exp(big_value_2->mantice));
  }
}

void cast_by_exp(s21_big_decimal *bdec, unsigned char exp) {
  unsigned char sign = 0;
  sign = get_sign(bdec->mantice);
  for (; exp > get_exp(bdec->mantice);) {
    *bdec = simple_mul(*bdec, bdec_ten);
    set_exp(&bdec->mantice, get_exp(bdec->mantice) + 1);
    set_sign(&bdec->mantice, sign);
  }
}

int big_to_dec(s21_big_decimal *bdec, s21_decimal *dec_rez) {
  int exp = get_exp(bdec->mantice);
  int sign = 0;
  int overflow = 0;
  sign = get_sign(bdec->mantice);

  // round fract part
  s21_big_decimal bdec_rounded = {0};
  // round fract part
  while (is_big_converted_to_dec(*bdec)) {
    if (!get_exp(bdec->mantice)) {
      overflow = 1;
      break;
    }

    // round fract part
    if (!check_high_ints_big(simple_div(*bdec, bdec_ten))) {
      bdec_rounded = *bdec;
    }

    *bdec = simple_div(*bdec, bdec_ten);
    set_exp(&bdec->mantice, --exp);
    set_sign(&bdec->mantice, sign);
  }

  if (!overflow) {
    // round fract part
    int fract_part = get_big_fract_part(bdec_rounded);
    int first_int_part = get_big_fract_part(*bdec);
    overflow = round_big_dec(bdec, fract_part, first_int_part);
    // round fract part

    fill_dec_from_big(*bdec, dec_rez);
  }

  return overflow;
}

unsigned char round_big_dec(s21_big_decimal *bdec_rounded, int fract_part,
                            int int_part) {
  unsigned char exp = get_exp(bdec_rounded->mantice);
  unsigned char sign = get_sign(bdec_rounded->mantice);

  int was_rounded = 0;
  if (get_exp(bdec_rounded->mantice) < 28) {
    if (fract_part > 4) {
      *bdec_rounded = simple_add(*bdec_rounded, bdec_one);
      was_rounded = 1;
    }
    if (int_part == 9 && was_rounded) {
      *bdec_rounded = simple_div(*bdec_rounded, bdec_ten);
      set_exp(&bdec_rounded->mantice, --exp);
      set_sign(&bdec_rounded->mantice, sign);
    }

  } else {
    if ((fract_part > 5) || ((fract_part == 5) && (int_part % 2 == 0))) {
      *bdec_rounded = simple_add(*bdec_rounded, bdec_one);
      was_rounded = 1;
    }
    if (int_part == 9 && was_rounded) {
      *bdec_rounded = simple_div(*bdec_rounded, bdec_ten);
      set_exp(&bdec_rounded->mantice, --exp);
      set_sign(&bdec_rounded->mantice, sign);
    }
    if ((fract_part == 0 || int_part == 0) && !was_rounded) {
      *bdec_rounded = simple_div(*bdec_rounded, bdec_ten);
      set_exp(&bdec_rounded->mantice, --exp);
      set_sign(&bdec_rounded->mantice, sign);
    }
  }

  return 0;
}

unsigned char get_big_fract_part(s21_big_decimal bdec) {
  s21_big_decimal bdec_fract = simple_mod(bdec, bdec_ten);
  return (unsigned char)bdec_fract.bits[0];
}

void fill_dec_from_big(s21_big_decimal bdec, s21_decimal *dec) {
  if (!is_empty_bdec(bdec)) {
    dec->bits[0] = bdec.bits[0];
    dec->bits[1] = bdec.bits[1];
    dec->bits[2] = bdec.bits[2];
    dec->bits[3] = bdec.mantice;
  }
}

unsigned char is_big_converted_to_dec(s21_big_decimal bdec) {
  return check_high_ints_big(bdec) || get_exp(bdec.mantice) > 28;
}

unsigned char check_high_ints_big(s21_big_decimal bdec) {
  return (bdec.bits[5] || bdec.bits[4] || bdec.bits[3]) ? 1 : 0;
}

s21_decimal simple_floor(s21_decimal dec) {
  s21_decimal dec_int = dec;
  if (get_exp(dec.bits[3])) {
    dec_int = reduce_exp_dec(dec, 0);
    s21_big_decimal bdec_1 = {0};
    bdec_1.bits[0] = 1;
    s21_big_decimal bdec = decimal_to_big(dec_int);
    if (get_sign(dec.bits[3])) {
      bdec = simple_add(bdec, bdec_1);
    }
    big_to_dec(&bdec, &dec_int);
    set_sign(&dec_int.bits[3], get_sign(dec.bits[3]));
  }
  return dec_int;
}

s21_decimal reduce_exp_dec(s21_decimal dec, unsigned char reduce_num) {
  s21_big_decimal bdec = decimal_to_big(dec);
  unsigned char exp = get_exp(bdec.mantice);
  unsigned char sign = get_sign(bdec.mantice);
  for (unsigned char i = 0; i < exp - reduce_num; i++) {
    bdec = simple_div(bdec, bdec_ten);
    set_exp(&bdec.mantice, exp - i - 1);
    set_sign(&bdec.mantice, sign);
  }
  s21_decimal rez = {0};
  big_to_dec(&bdec, &rez);
  return rez;
}

// for comparison
// big_dec1 < big_dec2, 0 - false, 1 - true
int s21_is_big_less(s21_big_decimal value_1, s21_big_decimal value_2) {
  if (get_sign(value_1.mantice) == 1 && get_sign(value_2.mantice) == 0) {
    return 1;  //
  }
  if (get_sign(value_1.mantice) == 0 && get_sign(value_2.mantice) == 1) {
    return 0;  //
  }

  for (int i = 5; i >= 0; i--) {
    if (value_1.bits[i] == value_2.bits[i]) {
      continue;
    }

    if (value_1.bits[i] < value_2.bits[i]) {
      if (get_sign(value_1.mantice) == 0) {
        return 1;
      } else {
        return 0;
      }
    } else {
      if (get_sign(value_1.mantice) == 0) {
        return 0;
      } else {
        return 1;
      }
    }
  }
  return 0;
}

// big_dec1 = big_dec2, 0 - false, 1 - true
int s21_is_big_equal(s21_big_decimal value_1, s21_big_decimal value_2) {
  int count = 0;
  if (get_sign(value_1.mantice) == get_sign(value_2.mantice)) {
    for (int i = 5; i >= 0; i--) {
      if (value_1.bits[i] == value_2.bits[i]) {
        count++;
      }
    }
  }
  return (count == 6) ? 1 : 0;
}

// big_dec1 > big_dec2, 0 - false, 1 - true
int s21_is_big_greater(s21_big_decimal value_1, s21_big_decimal value_2) {
  return (s21_is_big_less(value_1, value_2) == 0 &&
          s21_is_big_equal(value_1, value_2) == 0)
             ? 1
             : 0;
}

int s21_is_big_greater_or_equal(s21_big_decimal value_1,
                                s21_big_decimal value_2) {
  return (s21_is_big_less(value_1, value_2) == 1) ? 0 : 1;
}

// big_dec1 != big_dec2, 0 - false, 1 - true
int s21_is_not_big_equal(s21_big_decimal value_1, s21_big_decimal value_2) {
  return (s21_is_big_equal(value_1, value_2) ? 0 : 1);
}

// big_dec1 <= big_dec2, 0 - false, 1 - true
int s21_is_big_less_or_equal(s21_big_decimal value_1, s21_big_decimal value_2) {
  return (s21_is_big_greater(value_1, value_2) == 1) ? 0 : 1;
}

// comparison

// compare
int s21_is_big_to_equals(s21_big_decimal value_1, s21_big_decimal value_2) {
  for (int i = INT_BIG_DECIMAL - 1; i >= 0; i--) {
    if (value_1.bits[i] == 0 && value_2.bits[i] == 0) {
      continue;
    }
    if (value_1.bits[i] > value_2.bits[i]) {
      return 1;
    }
    if (value_1.bits[i] < value_2.bits[i]) {
      return 0;
    }
    if (value_1.bits[i] == value_2.bits[i]) {
      if (i == 0) return 1;
      continue;
    }
  }
  return 0;
}

// compare
