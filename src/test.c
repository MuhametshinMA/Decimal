#include "s21_decimal.h"
#include "s21_test.h"

int main(void) {
  {
    s21_decimal dec1 = set_decimal(0, 0, 0, 0, 0);
    s21_decimal dec2 = set_decimal(12, 0, 0, 15, 1);

    s21_decimal s_add = {0};
    s21_decimal ori_add = {0};
    int er = s21_div(dec1, dec2, &s_add);
    char *ori_adds = print_dec(ori_add);
    char *s_adds = print_dec(s_add);
    printf("ori:%s\ns21:%s\ner:%d\n", ori_adds, s_adds, er);
    free(ori_adds);
    free(s_adds);
  }
  {
    s21_decimal dec1 = set_decimal(-1, -1, -1, 0, 0);
    s21_decimal dec2 = set_decimal(12, 0, 0, 15, 0);

    s21_decimal s_add = {0};
    s21_decimal ori_add = {0};
    int er = s21_div(dec1, dec2, &s_add);
    char *ori_adds = print_dec(ori_add);
    char *s_adds = print_dec(s_add);
    ck_assert_str_eq(s_adds, ori_adds);
    ck_assert_int_eq(er, 1);
    free(ori_adds);
    free(s_adds);
  }
  {
    s21_decimal dec1 = set_decimal(-1, -1, -1, 0, 0);
    s21_decimal dec2 = set_decimal(0, 0, 0, 0, 0);

    s21_decimal s_add = {0};
    s21_decimal ori_add = {0};
    int er = s21_div(dec1, dec2, &s_add);
    char *ori_adds = print_dec(ori_add);
    char *s_adds = print_dec(s_add);
    printf("ori:%s\ns21:%s\ner:%d\n", ori_adds, s_adds, er);
    free(ori_adds);
    free(s_adds);
  }
  {
    s21_decimal dec1 = set_decimal(1, 0, 0, 0, 0);
    s21_decimal dec2 = set_decimal(1, 0, 0, 0, 0);

    s21_decimal s_add = {0};
    s21_decimal ori_add = {0};
    int er = s21_sub(dec1, dec2, &s_add);
    char *ori_adds = print_dec(ori_add);
    char *s_adds = print_dec(s_add);
    printf("ori:%s\ns21:%s\ner:%d\n", ori_adds, s_adds, er);
    free(ori_adds);
    free(s_adds);
  }
  {
    s21_decimal test_value_1 = {.bits = {1, 2, 3, 917504}};
    s21_decimal test_value_2 = {.bits = {1, 2, 3, -2146566144}};
    s21_decimal test_value_3 = {.bits = {33, 2, 3000, -2146107392}};

    char *s_divs1 = print_dec(test_value_1);
    char *s_divs2 = print_dec(test_value_2);
    char *s_divs3 = print_dec(test_value_3);

    s21_decimal res = {0};

    s21_div(test_value_2, test_value_1, &res);
    char *s_res = print_dec(res);

    printf("s21:%s\n", s_divs1);
    printf("s21:%s\n", s_divs2);
    printf("s21:%s\n", s_divs3);
    printf("res:%s\n", s_res);

    free(s_divs1);
    free(s_divs2);
    free(s_divs3);
  }
  {
    s21_decimal dec1 = set_decimal(77464295, 36840200, 66581759, 14, 1);
    s21_decimal dec2 = set_decimal(102463687, 127361613, 50830966, 7, 1);

    s21_decimal ori_mod = set_decimal(1050990712, 3069947510, 508309593, 8, 0);

    s21_decimal s_div = {0};
    s21_sub(dec1, dec2, &s_div);
    char *ori_divs = print_dec(ori_mod);
    char *s_divs = print_dec(s_div);
    printf("ori:%s\ns21:%s\n", ori_divs, s_divs);
    free(ori_divs);
    free(s_divs);
  }
  {
    s21_decimal dec1 = set_decimal(77464295, 36840200, 66581759, 14, 1);
    s21_decimal dec2 = set_decimal(102463687, 127361613, 50830966, 7, 1);

    s21_decimal ori_mod = set_decimal(3147328899, 34288121, 71, 28, 0);

    s21_decimal s_div = {0};
    s21_div(dec1, dec2, &s_div);
    char *ori_divs = print_dec(ori_mod);
    char *s_divs = print_dec(s_div);
    printf("ori:%s\ns21:%s\n", ori_divs, s_divs);
    free(ori_divs);
    free(s_divs);
  }
  {
    s21_decimal dec1 = set_decimal(90834837, 38081975, 160415414, 24, 1);
    s21_decimal dec2 = set_decimal(25202016, 150911068, 111608182, 23, 1);

    s21_decimal ori_mod = set_decimal(605817596, 945050144, 7791666, 27, 0);

    s21_decimal s_div = {0};
    s21_div(dec1, dec2, &s_div);
    char *ori_divs = print_dec(ori_mod);
    char *s_divs = print_dec(s_div);
    printf("ori:%s\ns21:%s\n", ori_divs, s_divs);
    free(ori_divs);
    free(s_divs);
  }
  {
    s21_decimal dec1 = set_decimal(1794453624, 898195748, 852708118, 17, 0);
    s21_decimal dec2 = set_decimal(1910540931, 1235965038, 9058638, 4, 1);

    s21_decimal ori_mod = set_decimal(3093014281, 1850305940, 57589432, 16, 1);

    s21_decimal s_div = {0};
    s21_div(dec2, dec1, &s_div);
    char *ori_divs = print_dec(ori_mod);
    char *s_divs = print_dec(s_div);
    printf("ori:%s\ns21:%s\n", ori_divs, s_divs);
    free(ori_divs);
    free(s_divs);
  }
  {
    s21_decimal dec1 = set_decimal(1823452201, 2063562674, 1006090516, 16, 1);
    s21_decimal dec2 = set_decimal(321316291, 727547957, 371183081, 24, 1);

    s21_decimal ori_mod = set_decimal(4016760276, 825885434, 1006090520, 16, 1);

    s21_decimal s_div = {0};
    s21_add(dec1, dec2, &s_div);
    char *ori_divs = print_dec(ori_mod);
    char *s_divs = print_dec(s_div);
    printf("ori:%s\ns21:%s\n", ori_divs, s_divs);
    free(ori_divs);
    free(s_divs);
  }

  {
    s21_decimal dec1 = set_decimal(1884035085, 249191858, 312639605, 14, 1);
    s21_decimal dec2 = set_decimal(1130500648, 1520515877, 747348886, 10, 1);

    s21_decimal ori_div = set_decimal(543870183, 3349140893, 2267, 27, 0);

    s21_decimal s_div = {0};
    s21_div(dec1, dec2, &s_div);
    char *ori_divs = print_dec(ori_div);
    char *s_divs = print_dec(s_div);
    printf("ori:%s\ns21:%s\n", ori_divs, s_divs);

    free(ori_divs);
    free(s_divs);
  }

  {
    s21_decimal dec1 = set_decimal(1551759323, 1605648963, 231934145, 12, 1);
    s21_decimal dec2 = set_decimal(1760480742, 1291077370, 79977411, 7, 1);

    s21_decimal ori_mod = set_decimal(804339024, 1806296325, 799797306, 8, 1);

    s21_decimal s_div = {0};
    s21_add(dec1, dec2, &s_div);
    char *ori_divs = print_dec(ori_mod);
    char *s_divs = print_dec(s_div);
    printf("ori:%s\ns21:%s\n", ori_divs, s_divs);
    free(ori_divs);
    free(s_divs);
  }

  {
    s21_decimal dec1 = set_decimal(1794453624, 898195748, 852708118, 17, 0);
    s21_decimal dec2 = set_decimal(1910540931, 1235965038, 9058638, 4, 1);

    s21_decimal ori_mod = set_decimal(3093014281, 1850305940, 57589432, 16, 1);

    s21_decimal s_div = {0};
    s21_div(dec2, dec1, &s_div);
    char *ori_divs = print_dec(ori_mod);
    char *s_divs = print_dec(s_div);
    printf("ori:%s\ns21:%s\n", ori_divs, s_divs);
    free(ori_divs);
    free(s_divs);
  }
  {
    s21_decimal dec1 = set_decimal(1551759323, 1605648963, 231934145, 12, 1);
    s21_decimal dec2 = set_decimal(1760480742, 1291077370, 79977411, 7, 1);

    s21_decimal ori_mod = set_decimal(4017593546, 389963184, 1572, 27, 0);

    s21_decimal s_div = {0};
    s21_div(dec1, dec2, &s_div);
    char *ori_divs = print_dec(ori_mod);
    char *s_divs = print_dec(s_div);
    printf("ori:%s\ns21:%s\n", ori_divs, s_divs);
    free(ori_divs);
    free(s_divs);
  }
  {
    s21_decimal dec1 = set_decimal(873386614, 805395647, 185116229, 23, 1);
    s21_decimal dec2 = set_decimal(678585236, 400547423, 258399284, 28, 0);

    s21_decimal ori_mod = set_decimal(1569025447, 3031580280, 756, 27, 1);

    s21_decimal s_div = {0};
    s21_div(dec2, dec1, &s_div);
    char *ori_divs = print_dec(ori_mod);
    char *s_divs = print_dec(s_div);
    printf("ori:%s\ns21:%s\n", ori_divs, s_divs);
    free(ori_divs);
    free(s_divs);
  }
  {
    s21_decimal dec1 = set_decimal(285535726, 491995961, 72631439, 1, 1);
    s21_decimal dec2 = set_decimal(1411151558, 1646308160, 647050305, 2, 1);

    s21_decimal ori_mod = set_decimal(3371172639, 4269005249, 608508823, 28, 0);

    s21_decimal s_div = {0};
    s21_div(dec1, dec2, &s_div);
    char *ori_divs = print_dec(ori_mod);
    char *s_divs = print_dec(s_div);
    printf("ori:%s\ns21:%s\n", ori_divs, s_divs);
    free(ori_divs);
    free(s_divs);
  }
  {
    s21_decimal dec1 = set_decimal(1954850797, 493583905, 572174246, 6, 0);
    s21_decimal dec2 = set_decimal(217677280, 307069616, 588239620, 25, 0);

    s21_decimal ori_add = set_decimal(3039961370, 493583905, 572174246, 6, 0);

    s21_decimal s_add = {0};
    s21_add(dec1, dec2, &s_add);
    char *ori_adds = print_dec(ori_add);
    char *s_adds = print_dec(s_add);
    printf("ori:%s\ns21:%s\n", ori_adds, s_adds);
    free(ori_adds);
    free(s_adds);
  }
  {
    float fl_1 = 6347073846.0079878f;
    char *str_fl_1 = "0 0 0 1 2052106704\n";
    s21_decimal s21_ftod_1 = {0};
    s21_from_float_to_decimal(fl_1, &s21_ftod_1);
    char *s21_str_1 = print_dec(s21_ftod_1);
    printf("ori:%s\ns21:%s\n", str_fl_1, s21_str_1);
    free(s21_str_1);

    float fl_2 = 73846.0000079878f;
    char *str_fl_2 = "0 0 0 0 73846\n";
    s21_decimal s21_ftod_2 = {0};
    s21_from_float_to_decimal(fl_2, &s21_ftod_2);
    char *s21_str_2 = print_dec(s21_ftod_2);
    printf("ori:%s\ns21:%s\n", str_fl_2, s21_str_2);
    free(s21_str_2);

    float fl_3 = 73846.79878f;
    char *str_fl_3 = "0 1 0 0 738468\n";
    s21_decimal s21_ftod_3 = {0};
    s21_from_float_to_decimal(fl_3, &s21_ftod_3);
    char *s21_str_3 = print_dec(s21_ftod_3);
    printf("ori:%s\ns21:%s\n", str_fl_3, s21_str_3);
    free(s21_str_3);
  }
  {
    float fl_8 = 3.74e-21f;
    char *str_fl_8 = "0 23 0 0 374\n";
    s21_decimal s21_ftod_8 = {0};
    s21_from_float_to_decimal(fl_8, &s21_ftod_8);
    char *s21_str_8 = print_dec(s21_ftod_8);
    printf("ori:%s\ns21:%s\n", str_fl_8, s21_str_8);
    free(s21_str_8);

    float fl_9 = -.000000000001009887879878f;
    char *str_fl_9 = "1 18 0 0 1009888\n";
    s21_decimal s21_ftod_9 = {0};
    s21_from_float_to_decimal(fl_9, &s21_ftod_9);
    char *s21_str_9 = print_dec(s21_ftod_9);
    printf("ori:%s\ns21:%s\n", str_fl_9, s21_str_9);
    free(s21_str_9);
  }

  return 0;
}
