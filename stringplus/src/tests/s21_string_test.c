#include "../s21_string.h"

#include <check.h>
#include <stdio.h>
#include <string.h>

START_TEST(s21_strncatTest) {
  char srcS[100] = "Hello";
  char srcD[100] = "Hello";
  char str[100] = " World";
  s21_strncat(srcS, str, 5);
  strncat(srcD, str, 5);
  ck_assert_str_eq(srcD, srcS);
  char srcS2[100] = "I'm";
  char srcD2[100] = "I'm";
  char str2[100] = "Sorry";
  char *resS = s21_strncat(srcS, str2, 3);
  char *resD = strncat(srcD, str2, 3);
  ck_assert_str_eq(resS, resD);
  ck_assert_str_eq(srcS2, srcD2);
  char srcS3[100] = "Sigma";
  char srcD3[100] = "Sigma";
  char str3[100] = "";
  s21_strncat(srcS3, str3, 5);
  strncat(srcD3, str3, 5);
  ck_assert_str_eq(srcS3, srcD3);
  char srcS4[100] = "";
  char srcD4[100] = "";
  char str4[100] = "Sigma";
  s21_strncat(srcS4, str4, 5);
  strncat(srcD4, str4, 5);
  ck_assert_str_eq(srcS4, srcD4);
  char srcS5[100] = "";
  char srcD5[100] = "";
  char str5[100] = "";
  s21_strncat(srcS5, str5, 0);
  strncat(srcD5, str5, 0);
  ck_assert_str_eq(srcS5, srcD5);
}
END_TEST

START_TEST(s21_strlenTest) {
  char test_1[] = "SkyMage";
  char test_2[] = " ";
  char test_3[] = "\\\000";
  char test_4[] = "Hello World";
  char test_5[] = "1\0";
  char test_6[] = "1\0234567";
  char test_7[] = "";
  char test_8[] = "t";
  ck_assert_int_eq(s21_strlen(test_1), strlen(test_1));
  ck_assert_int_eq(s21_strlen(test_2), strlen(test_2));
  ck_assert_int_eq(s21_strlen(test_3), strlen(test_3));
  ck_assert_int_eq(s21_strlen(test_4), strlen(test_4));
  ck_assert_int_eq(s21_strlen(test_5), strlen(test_5));
  ck_assert_int_eq(s21_strlen(test_6), strlen(test_6));
  ck_assert_int_eq(s21_strlen(test_7), strlen(test_7));
  ck_assert_int_eq(s21_strlen(test_8), strlen(test_8));
}
END_TEST

START_TEST(s21_strcspnTest) {
  char str1[] = "LOST: 4-8-15-16-23-42";
  char keys1[] = "1234567890";
  char str2[] = "12356";
  char keys2[] = "7890";
  char str3[] = "Pudge";
  char keys3[] = "";
  char str4[] = "";
  char keys4[] = "Gulya";
  char str5[] = "";
  char keys5[] = "";
  ck_assert_int_eq(s21_strcspn(str1, keys1), strcspn(str1, keys1));
  ck_assert_int_eq(s21_strcspn(str2, keys2), strcspn(str2, keys2));
  ck_assert_int_eq(s21_strcspn(str3, keys3), strcspn(str3, keys3));
  ck_assert_int_eq(s21_strcspn(str4, keys4), strcspn(str4, keys4));
  ck_assert_int_eq(s21_strcspn(str5, keys5), strcspn(str5, keys5));
}
END_TEST

START_TEST(s21_strtokTest) {
  char my_str0[] = "BIBA";
  char my_delim0[] = " ";
  char origin_str0[] = "BIBA";
  char origin_delim0[] = " ";
  char *my_strtok = s21_strtok(my_str0, my_delim0);
  char *origin_strtok = strtok(origin_str0, origin_delim0);
  ck_assert_str_eq(my_strtok, origin_strtok);
  char my_str1[] = "AK-47/AWP-SSG MAC10,-/UMP ";
  char my_delim1[] = "/-, ";
  char origin_str1[] = "AK-47/AWP-SSG MAC10,-/UMP ";
  char origin_delim1[] = "/-, ";
  my_strtok = s21_strtok(my_str1, my_delim1);
  origin_strtok = strtok(origin_str1, origin_delim1);
  while (origin_strtok != s21_NULL) {
    ck_assert_str_eq(my_strtok, origin_strtok);
    my_strtok = s21_strtok(s21_NULL, my_delim1);
    origin_strtok = strtok(s21_NULL, origin_delim1);
  }
}
END_TEST

START_TEST(s21_memcpyTest) {
  char textS[100] = "Stariy";
  char textD[100] = "Stariy";
  char str[100] = "Molody";
  s21_memcpy(textS, str, 6);
  memcpy(textD, str, 6);
  ck_assert_str_eq(textS, textD);

  char textS1[100] = "Stariy";
  char textD1[100] = "Stariy";
  char str1[100] = "Bog";
  char *returnS1 = s21_memcpy(textS1, str1, 3);
  char *returnD1 = memcpy(textD1, str1, 3);
  ck_assert_str_eq(textS1, textD1);
  ck_assert_str_eq(returnS1, returnD1);

  char textS2[100] = "Nikita";
  char textD2[100] = "Nikita";
  char str2[100] = "Byyyanov LOX";
  char *returnS2 = s21_memcpy(textS2, str2, 13);
  char *returnD2 = memcpy(textD2, str2, 13);
  ck_assert_str_eq(textS2, textD2);
  ck_assert_str_eq(returnS2, returnD2);

  char textS3[100] = "Nikita";
  char textD3[100] = "Nikita";
  char str3[100] = "\6/6";
  char *returnS3 = s21_memcpy(textS3, str3, 4);
  char *returnD3 = memcpy(textD3, str3, 4);
  ck_assert_str_eq(textS3, textD3);
  ck_assert_str_eq(returnS3, returnD3);
  char textS4[100] = "Nikita";
  char textD4[100] = "Nikita";
  char str4[100] = "";
  char *returnS4 = s21_memcpy(textS4, str4, 4);
  char *returnD4 = memcpy(textD4, str4, 4);
  ck_assert_str_eq(textS4, textD4);
  ck_assert_str_eq(returnS4, returnD4);

  char textS5[100] = "";
  char textD5[100] = "";
  char str5[100] = "HolaBola";
  char *returnS5 = s21_memcpy(textS5, str5, 4);
  char *returnD5 = memcpy(textD5, str5, 4);
  ck_assert_str_eq(textS5, textD5);
  ck_assert_str_eq(returnS5, returnD5);
}
END_TEST

START_TEST(s21_to_upperTest) {
  char test_1[] = "pudge123";
  char test_2[] = "";
  char test_3[] =
      "a book or other written or printed work, regarded in terms of its "
      "content rather than its physical form.";
  char *test_4 = s21_NULL;

  char *res1 = s21_to_upper(test_1);
  char *res2 = s21_to_upper(test_2);
  char *res3 = s21_to_upper(test_3);
  char *res4 = s21_to_upper(test_4);

  ck_assert_str_eq(res1, "PUDGE123");
  ck_assert_str_eq(res3,
                   "A BOOK OR OTHER WRITTEN OR PRINTED WORK, REGARDED IN TERMS "
                   "OF ITS CONTENT RATHER THAN ITS PHYSICAL FORM.");
  ck_assert(res4 == s21_NULL);

  free(res1);
  free(res2);
  free(res3);
  free(res4);
}
END_TEST

START_TEST(s21_memcmpTest) {
  char srcS[100] = "hello";
  char srcD[100] = "hello";
  char str[100] = "HWo";
  ck_assert_uint_eq(s21_memcmp(srcS, str, 1) > 0, memcmp(srcD, str, 1) > 0);
  char pudge[100] = "PUDGE";
  char pudge2[100] = "PIDGE";
  char str2[100] = "Sorry";
  ck_assert_uint_eq(s21_memcmp(pudge, str2, 1) == 0,
                    memcmp(pudge2, str2, 1) == 0);
  char primal[100] = "primal";
  char primal2[100] = "primal";
  char str3[100] = " pramal";
  ck_assert_int_eq(s21_memcmp(primal, str3, 1) == -1,
                   memcmp(primal2, str3, 1) == -1);
  char srcS2[100] = "I'm";
  char srcD2[100] = "I'm";
  char str4[100] = "imsorry";
  ck_assert_uint_eq(s21_memcmp(srcS2, str4, 1) > 0, memcmp(srcD2, str4, 1) > 0);
  char pust[100] = "";
  char pust2[100] = "";
  char pust3[100] = "";
  ck_assert_uint_eq(s21_memcmp(pust, pust3, 1) == 0,
                    memcmp(pust2, pust3, 1) == 0);
}
END_TEST

START_TEST(s21_strncmpTest) {
  char srcS[100] = "Hello";
  char srcD[100] = "Hello";
  char str[100] = "hWorld";
  ck_assert_uint_eq(s21_strncmp(srcS, str, 1) > 0, strncmp(srcD, str, 1) > 0);
  char pudge[100] = "PUDGE";
  char pudge2[100] = "PIDGE";
  char str2[100] = "Sorry";
  ck_assert_uint_eq(s21_strncmp(pudge, str2, 1) == 0,
                    strncmp(pudge2, str2, 1) == 0);
  char primal[100] = "primal";
  char primal2[100] = "primal";
  char str3[100] = " pramal";
  ck_assert_int_eq(s21_strncmp(primal, str3, 1) == -1,
                   strncmp(primal2, str3, 1) == -1);
  char srcS2[100] = "I'm";
  char srcD2[100] = "I'm";
  char str4[100] = "imsorry";
  ck_assert_uint_eq(s21_strncmp(srcS2, str4, 1) > 0,
                    strncmp(srcD2, str4, 1) > 0);
  char pust[100] = "";
  char pust2[100] = "";
  char pust3[100] = "";
  ck_assert_uint_eq(s21_strncmp(pust, pust3, 1) == 0,
                    strncmp(pust2, pust3, 1) == 0);
}
END_TEST

START_TEST(s21_to_lowerTest) {
  char test_1[] = "PUDGE123";
  char test_2[] = "";
  char test_3[] = "A BOOK OR OTHER WRITTEN OR PRINTED WORK";
  char *test_4 = s21_NULL;
  char *res1 = s21_to_lower(test_1);
  char *res2 = s21_to_lower(test_2);
  char *res3 = s21_to_lower(test_3);
  char *res4 = s21_to_lower(test_4);
  ck_assert_str_eq(res1, "pudge123");
  ck_assert_str_eq(res3, "a book or other written or printed work");
  ck_assert(res4 == s21_NULL);
  free(res1);
  free(res2);
  free(res3);
  free(res4);
}
END_TEST

START_TEST(s21_insertTest) {
  char *src = "PUDGE";
  char *str = ", Lovers";
  char *res1 = s21_insert(src, str, 0);
  ck_assert_str_eq(res1, ", LoversPUDGE");
  free(res1);
  res1 = s21_insert(src, str, 100);
  ck_assert(res1 == s21_NULL);
  free(res1);
  res1 = s21_insert("", "", 0);
  free(res1);
  res1 = s21_insert(src, str, 2);
  ck_assert_str_eq(res1, "PU, LoversDGE");
  free(res1);
}
END_TEST

START_TEST(s21_memsetTest) {
  char arr1[100] = "";
  char arr2[100] = "";
  s21_memset(arr1, '1', 4);
  memset(arr2, '1', 4);
  ck_assert_str_eq(arr1, arr2);

  char arr3[100] = "";
  char arr4[100] = "";
  char *returnArr1 = s21_memset(arr3, 0, 100);
  char *returnArr2 = memset(arr4, 0, 100);
  ck_assert_str_eq(arr3, arr4);
  ck_assert_str_eq(returnArr1, returnArr2);

  char arr5[100] = "yfvyvytvyv";
  char arr6[100] = "ihbyhubugb";
  char *returnArr3 = s21_memset(arr5, 0, 100);
  char *returnArr4 = memset(arr6, 0, 100);
  ck_assert_str_eq(arr5, arr6);
  ck_assert_str_eq(returnArr3, returnArr4);

  char arr7[100] = "yfvyvytvyv";
  char arr8[100] = "yfvyvytvyv";
  char *returnArr5 = s21_memset(arr7, '\n', 1);
  char *returnArr6 = memset(arr8, '\n', 1);
  ck_assert_str_eq(arr7, arr8);
  ck_assert_str_eq(returnArr5, returnArr6);
}
END_TEST

START_TEST(s21_strncpyTest) {
  char dstF[100] = "123456789";
  char dstS[100] = "123456789";
  char srcStrn[100] = "12345\0006789";
  s21_strncpy(dstF, srcStrn, 3);
  strncpy(dstS, srcStrn, 3);
  ck_assert_str_eq(dstF, dstS);

  char dstF1[100] = "987654321";
  char dstS1[100] = "987654321";
  char srcStrn1[100] = "666/7890";
  char *copyArrF = s21_strncpy(dstF1, srcStrn1, 6);
  char *copyArrS = strncpy(dstS1, srcStrn1, 6);
  ck_assert_str_eq(copyArrF, copyArrS);

  char dstF2[100] = "";
  char dstS2[100] = "";
  char srcStrn2[100] = "765476543";
  char *copyArrF1 = s21_strncpy(dstF2, srcStrn2, 2);
  char *copyArrS1 = strncpy(dstS2, srcStrn2, 2);
  ck_assert_str_eq(copyArrF1, copyArrS1);

  char dstF3[100] = "1234567890";
  char dstS3[100] = "1234567890";
  char srcStrn3[100] = "";
  char *copyArrF2 = s21_strncpy(dstF3, srcStrn3, 2);
  char *copyArrS2 = strncpy(dstS3, srcStrn3, 2);
  ck_assert_str_eq(copyArrF2, copyArrS2);
}
END_TEST

START_TEST(s21_strstrTest) {
  char src1[100] = "super";
  char src2[100] = "super";
  char strQ[100] = "s";
  char *res1 = s21_strstr(src1, strQ);
  char *res2 = strstr(src2, strQ);
  ck_assert_str_eq(res1, res2);
  char src12[100] = "sigmach";
  char src22[100] = "sigmach";
  char strQ2[100] = "";
  char *resQ = s21_strstr(src12, strQ2);
  char *resW = strstr(src22, strQ2);
  ck_assert_str_eq(resQ, resW);
  char src3[100] = "primal";
  char src4[100] = "primal";
  char strQ3[100] = "t";
  char *res3 = s21_strstr(src3, strQ3);
  char *res4 = strstr(src4, strQ3);
  ck_assert_int_eq(res3 == s21_NULL, res4 == s21_NULL);
  char src8[100] = "";
  char src9[100] = "";
  char strQ9[100] = "";
  char *res5 = s21_strstr(src8, strQ9);
  char *res6 = strstr(src9, strQ9);
  ck_assert_int_eq(res5 == s21_NULL, res6 == s21_NULL);
}
END_TEST

START_TEST(s21_strpbrkTest) {
  char src1[100] = "superp";
  char src2[100] = "superp";
  char strQ[100] = "p";
  char *res1 = s21_strpbrk(src1, strQ);
  char *res2 = strpbrk(src2, strQ);
  ck_assert_str_eq(res1, res2);
  char src12[100] = "sigmach";
  char src22[100] = "sigmach";
  char strQ2[100] = "";
  char *resQ = s21_strpbrk(src12, strQ2);
  char *resW = strpbrk(src22, strQ2);
  ck_assert_int_eq(resQ == s21_NULL, resW == s21_NULL);
  char src3[100] = "primal";
  char src4[100] = "primal";
  char strQ3[100] = "t";
  char *res3 = s21_strpbrk(src3, strQ3);
  char *res4 = strpbrk(src4, strQ3);
  ck_assert_int_eq(res3 == s21_NULL, res4 == s21_NULL);
  char pust[100] = "primal";
  char pust2[100] = "primal";
  char strQ10[100] = "t";
  char *res5 = s21_strpbrk(pust, strQ10);
  char *res6 = strpbrk(pust2, strQ10);
  ck_assert_int_eq(res5 == s21_NULL, res6 == s21_NULL);
}
END_TEST

START_TEST(s21_trimTest) {
  char test_1[] = "            pudge123      ";
  char test_2[] = "";
  char test_3[] = "       a book or other written or printed work       ";
  char test_4[] = "       ";
  char test_5[] = " a book or other written      or printed work";
  char trimchars[] = " ";
  char trimchars2[] = " ";
  char trimchars3[] = " ";
  char trimchars4[] = " ";
  char trimchars5[] = " ";

  char *res1 = s21_trim(test_1, trimchars);
  char *res2 = s21_trim(test_2, trimchars2);
  char *res3 = s21_trim(test_3, trimchars3);
  char *res4 = s21_trim(test_4, trimchars4);
  char *res5 = s21_trim(test_5, trimchars5);

  ck_assert_str_eq(res1, "pudge123");
  ck_assert_str_eq(res2, "");
  ck_assert_str_eq(res3, "a book or other written or printed work");
  ck_assert_str_eq(res4, "");
  ck_assert_str_eq(res5, "a book or other written      or printed work");
  free(res1);
  free(res2);
  free(res3);
  free(res4);
  free(res5);
}
END_TEST
START_TEST(s21_memchrTest) {
  char src1[100] = "super";
  char src2[100] = "super";
  char strQ = 's';
  char *res1 = s21_memchr(src1, strQ, 4);
  char *res2 = memchr(src2, strQ, 4);
  ck_assert_str_eq(res1, res2);
  char src12[100] = "sigma";
  char src22[100] = "sigma";
  char strQ2 = 'g';
  char *resQ = s21_memchr(src12, strQ2, 100);
  char *resW = memchr(src22, strQ2, 100);
  ck_assert_str_eq(resQ, resW);
  char src13[100] = "";
  char src23[100] = "";
  char strQ3 = 'g';
  char *resE = s21_memchr(src13, strQ3, 100);
  char *resR = memchr(src23, strQ3, 100);
  ck_assert_int_eq(resE == s21_NULL, resR == s21_NULL);
  char src14[100] = "";
  char src24[100] = "";
  char strQ4 = '\0';
  char *resT = s21_memchr(src14, strQ4, 100);
  char *resY = memchr(src24, strQ4, 100);
  ck_assert_int_eq(resT == s21_NULL, resY == s21_NULL);
  ck_assert_str_eq(resT, resY);
}
END_TEST

START_TEST(s21_strchrTest) {
  char str1[] = "Hello, World!";
  ck_assert_str_eq(s21_strchr(str1, 'o'), strchr(str1, 'o'));
  char str2[] = "Hello, World!";
  ck_assert_int_eq(s21_strchr(str2, 'x') == s21_NULL,
                   strchr(str2, 'x') == s21_NULL);
  char str3[] = "Hello, World!";
  ck_assert_str_eq(s21_strchr(str3, 'H'), strchr(str3, 'H'));
  char str4[] = "Hello, World!";
  ck_assert_str_eq(s21_strchr(str4, '!'), strchr(str4, '!'));
  char str5[] = "Hello, World!";
  ck_assert_str_eq(s21_strchr(str5, '\0'), strchr(str5, '\0'));
  char str6[] = "";
  ck_assert_int_eq(s21_strchr(str6, 'a') == s21_NULL,
                   strchr(str6, 'a') == s21_NULL);
  char str7[] = "aaaaa";
  ck_assert_str_eq(s21_strchr(str7, 'a'), strchr(str7, 'a'));
  char str8[] = "";
  ck_assert_str_eq(s21_strchr(str8, '\0'), strchr(str8, '\0'));
}
END_TEST

START_TEST(s21_strrchrTest) {
  char str1[] = "Hello, World!";
  ck_assert_str_eq(s21_strrchr(str1, 'o'), strrchr(str1, 'o'));
  char str2[] = "Hello, World!";
  ck_assert_int_eq(s21_strrchr(str2, 'x') == s21_NULL,
                   strrchr(str2, 'x') == s21_NULL);

  char str3[] = "Hello, World!";
  ck_assert_str_eq(s21_strrchr(str3, 'H'), strrchr(str3, 'H'));
  char str4[] = "Hello, World!";
  ck_assert_str_eq(s21_strrchr(str4, '!'), strrchr(str4, '!'));
  char str5[] = "Hello, World!";
  ck_assert_str_eq(s21_strrchr(str5, '\0'), strrchr(str5, '\0'));
  char str6[] = "";
  ck_assert_int_eq(s21_strrchr(str6, 'a') == s21_NULL,
                   strrchr(str6, 'a') == s21_NULL);
  char str7[] = "aaaaa";
  ck_assert_str_eq(s21_strrchr(str7, 'a'), strrchr(str7, 'a'));
  char str8[] = "";
  ck_assert_str_eq(s21_strrchr(str8, '\0'), strrchr(str8, '\0'));
}
END_TEST

START_TEST(s21_sprintf_spec_pTest) {
  int p1 = 10;
  char strS1[100] = {0};
  char strD1[100] = {0};
  int lenS1 = s21_sprintf(strS1, "%p", &p1);
  int lenD1 = sprintf(strD1, "%p", &p1);
  ck_assert_str_eq(strS1, strD1);
  ck_assert_int_eq(lenD1, lenS1);
  char p2 = 'z';
  char strS2[100] = {0};
  char strD2[100] = {0};
  int lenS2 = s21_sprintf(strS2, "%-20p", &p2);
  int lenD2 = sprintf(strD2, "%-20p", &p2);
  ck_assert_str_eq(strS2, strD2);
  ck_assert_int_eq(lenD2, lenS2);
  float p3 = 10.1;
  char strS3[100] = {0};
  char strD3[100] = {0};
  int lenS3 = s21_sprintf(strS3, "%20p", &p3);
  int lenD3 = sprintf(strD3, "%20p", &p3);
  ck_assert_int_eq(lenD3, lenS3);
  ck_assert_str_eq(strS3, strD3);
}
END_TEST

START_TEST(s21_sprintf_spec_cTest) {
  int p1 = 10;
  char strS1[100] = {0};
  char strD1[100] = {0};
  int lenS1 = s21_sprintf(strS1, "%c", p1);
  int lenD1 = sprintf(strD1, "%c", p1);
  ck_assert_int_eq(lenD1, lenS1);
  ck_assert_str_eq(strS1, strD1);
  char p2 = 'z';
  char strS2[100] = {0};
  char strD2[100] = {0};
  int lenS2 = s21_sprintf(strS2, "%-20c", p2);
  int lenD2 = sprintf(strD2, "%-20c", p2);
  ck_assert_int_eq(lenD2, lenS2);
  ck_assert_str_eq(strS2, strD2);
  int p3 = 123;
  char strS3[100] = {0};
  char strD3[100] = {0};
  int lenS3 = s21_sprintf(strS3, "%20c", p3);
  int lenD3 = sprintf(strD3, "%20c", p3);
  ck_assert_int_eq(lenD3, lenS3);
  ck_assert_str_eq(strS3, strD3);
  int p4 = 't';
  char strS4[100] = {0};
  char strD4[100] = {0};
  int lenS4 = s21_sprintf(strS4, "%20lc", p4);
  int lenD4 = sprintf(strD4, "%20lc", p4);
  ck_assert_int_eq(lenD4, lenS4);
  ck_assert_str_eq(strS4, strD4);
}
END_TEST

START_TEST(s21_sprintf_spec_oTest) {
  unsigned int p1 = 456;
  char strS1[1000] = {0};
  char strD1[1000] = {0};
  int lenS1 = s21_sprintf(strS1, "ya molodec %o", p1);
  int lenD1 = sprintf(strD1, "ya molodec %o", p1);
  ck_assert_int_eq(lenD1, lenS1);
  ck_assert_str_eq(strS1, strD1);
  unsigned long int p2 = 2975274;
  char strS2[1000] = {0};
  char strD2[1000] = {0};
  int lenS2 = s21_sprintf(strS2, "%-20lo", p2);
  int lenD2 = sprintf(strD2, "%-20lo", p2);
  ck_assert_int_eq(lenD2, lenS2);
  ck_assert_str_eq(strS2, strD2);
  unsigned short int p3 = 37;
  char strS3[1000] = {0};
  char strD3[1000] = {0};
  int lenS3 = s21_sprintf(strS3, "%20ho", p3);
  int lenD3 = sprintf(strD3, "%20ho", p3);
  ck_assert_int_eq(lenD3, lenS3);
  ck_assert_str_eq(strS3, strD3);
  unsigned int p4 = 37;
  char strS4[1000] = {0};
  char strD4[1000] = {0};
  int lenS4 = s21_sprintf(strS4, "%#25.*o", 20, p4);
  int lenD4 = sprintf(strD4, "%#25.*o", 20, p4);
  ck_assert_str_eq(strS4, strD4);
  ck_assert_int_eq(lenD4, lenS4);
  unsigned int p5 = 37;
  char strS5[1000] = {0};
  char strD5[1000] = {0};
  int lenS5 = s21_sprintf(strS5, "%#-*.20o", 25, p5);
  int lenD5 = sprintf(strD5, "%#-*.20o", 25, p5);
  ck_assert_int_eq(lenD5, lenS5);
  ck_assert_str_eq(strS5, strD5);
  unsigned int p6 = 37;
  char strS6[1000] = {0};
  char strD6[1000] = {0};
  int lenS6 = s21_sprintf(strS6, "%#030o", p6);
  int lenD6 = sprintf(strD6, "%#030o", p6);
  ck_assert_str_eq(strS6, strD6);
  ck_assert_int_eq(lenD6, lenS6);
}
END_TEST

START_TEST(s21_sprintf_spec_x_XTest) {
  unsigned int p1 = 456;
  char strS1[1000] = {0};
  char strD1[1000] = {0};
  int lenS1 = s21_sprintf(strS1, "%x", p1);
  int lenD1 = sprintf(strD1, "%x", p1);
  ck_assert_int_eq(lenD1, lenS1);
  ck_assert_str_eq(strS1, strD1);
  unsigned long int p2 = 2975274;
  char strS2[1000] = {0};
  char strD2[1000] = {0};
  int lenS2 = s21_sprintf(strS2, "%-20lX", p2);
  int lenD2 = sprintf(strD2, "%-20lX", p2);
  ck_assert_int_eq(lenD2, lenS2);
  ck_assert_str_eq(strS2, strD2);
  unsigned short int p3 = 37;
  char strS3[1000] = {0};
  char strD3[1000] = {0};
  int lenS3 = s21_sprintf(strS3, "%20hX", p3);
  int lenD3 = sprintf(strD3, "%20hX", p3);
  ck_assert_int_eq(lenD3, lenS3);
  ck_assert_str_eq(strS3, strD3);
  unsigned long int p4 = 37;
  char strS4[1000] = {0};
  char strD4[1000] = {0};
  int lenS4 = s21_sprintf(strS4, "%#25.20lx", p4);
  int lenD4 = sprintf(strD4, "%#25.20lx", p4);
  ck_assert_str_eq(strS4, strD4);
  ck_assert_int_eq(lenD4, lenS4);
  unsigned int p5 = 37;
  char strS5[1000] = {0};
  char strD5[1000] = {0};
  int lenS5 = s21_sprintf(strS5, "%#-*.20X", 25, p5);
  int lenD5 = sprintf(strD5, "%#-*.20X", 25, p5);
  ck_assert_int_eq(lenD5, lenS5);
  ck_assert_str_eq(strS5, strD5);
  unsigned int p7 = 40;
  char strS7[1000] = {0};
  char strD7[1000] = {0};
  int lenS7 = s21_sprintf(strS7, "%#x", p7);
  int lenD7 = sprintf(strD7, "%#x", p7);
  ck_assert_str_eq(strS7, strD7);
  ck_assert_int_eq(lenD7, lenS7);
  unsigned int p8 = 0;
  char strS8[1000] = {0};
  char strD8[1000] = {0};
  int lenS8 = s21_sprintf(strS8, "%#x", p8);
  int lenD8 = sprintf(strD8, "%#x", p8);
  ck_assert_str_eq(strS8, strD8);
  ck_assert_int_eq(lenD8, lenS8);
  unsigned int p9 = 0;
  char strS9[1000] = {0};
  char strD9[1000] = {0};
  int lenS9 = s21_sprintf(strS9, "%020x", p9);
  int lenD9 = sprintf(strD9, "%020x", p9);
  ck_assert_str_eq(strS9, strD9);
  ck_assert_int_eq(lenD9, lenS9);
}
END_TEST

START_TEST(s21_sprintf_spec_dTest) {
  int d1 = 123;
  char str1[100] = {0};
  char str2[100] = {0};
  int intD1 = s21_sprintf(str1, "%d", d1);
  int intD2 = sprintf(str2, "%d", d1);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(intD1, intD2);
  int d2 = 123;
  char str3[100] = {0};
  char str4[100] = {0};
  int intD3 = s21_sprintf(str3, "%+d", d2);
  int intD4 = sprintf(str4, "%+d", d2);
  ck_assert_str_eq(str3, str4);
  ck_assert_int_eq(intD3, intD4);
  int d3 = -123;
  char str5[100] = {0};
  char str6[100] = {0};
  int intD5 = s21_sprintf(str5, "%-+d", d3);
  int intD6 = sprintf(str6, "%-+d", d3);
  ck_assert_str_eq(str5, str6);
  ck_assert_int_eq(intD5, intD6);
  int d4 = -123;
  char str7[100] = {0};
  char str8[100] = {0};
  int intD7 = s21_sprintf(str7, "%-d", d4);
  int intD8 = sprintf(str8, "%-d", d4);
  ck_assert_str_eq(str7, str8);
  ck_assert_int_eq(intD7, intD8);
  int d5 = -123;
  char str9[100] = {0};
  char str10[100] = {0};
  int intD9 = s21_sprintf(str9, "%-+d", d5);
  int intD10 = sprintf(str10, "%-+d", d5);
  ck_assert_str_eq(str9, str10);
  ck_assert_int_eq(intD9, intD10);

  int a1 = -123;
  char strr1[100] = {0};
  char strr2[100] = {0};
  int intDD1 = s21_sprintf(strr1, "%0d", a1);
  int intDD2 = sprintf(strr2, "%0d", a1);
  ck_assert_str_eq(strr1, strr2);
  ck_assert_int_eq(intDD1, intDD2);

  int a2 = -123;
  char strr3[100] = {0};
  char strr4[100] = {0};
  int intDD3 = s21_sprintf(strr3, "%+0d", a2);
  int intDD4 = sprintf(strr4, "%+0d", a2);
  ck_assert_str_eq(strr3, strr4);
  ck_assert_int_eq(intDD3, intDD4);

  int a3 = 123;
  char strr5[100] = {0};
  char strr6[100] = {0};
  int intDD5 = s21_sprintf(strr5, "% 0d", a3);
  int intDD6 = sprintf(strr6, "% 0d", a3);
  ck_assert_str_eq(strr5, strr6);
  ck_assert_int_eq(intDD5, intDD6);

  int a4 = -123;
  char strr7[100] = {0};
  char strr8[100] = {0};
  int intDD7 = s21_sprintf(strr7, "% 0d", a4);
  int intDD8 = sprintf(strr8, "% 0d", a4);
  ck_assert_str_eq(strr7, strr8);
  ck_assert_int_eq(intDD7, intDD8);

  int a5 = 123;
  char strr9[100] = {0};
  char strr10[100] = {0};
  int intDD9 = s21_sprintf(strr9, "% d", a5);
  int intDD10 = sprintf(strr10, "% d", a5);
  ck_assert_str_eq(strr9, strr10);
  ck_assert_int_eq(intDD9, intDD10);

  int a6 = 123;
  char strr11[100] = {0};
  char strr12[100] = {0};
  int intDD11 = s21_sprintf(strr11, "%15.10d", a6);
  int intDD12 = sprintf(strr12, "%15.10d", a6);
  ck_assert_str_eq(strr11, strr12);
  ck_assert_int_eq(intDD11, intDD12);

  int a7 = 123;
  char strr13[100] = {0};
  char strr14[100] = {0};
  int intDD13 = s21_sprintf(strr13, "%-15d", a7);
  int intDD14 = sprintf(strr14, "%-15d", a7);
  ck_assert_str_eq(strr13, strr14);
  ck_assert_int_eq(intDD13, intDD14);

  int a8 = -123;
  char strr15[100] = {0};
  char strr16[100] = {0};
  int intDD15 = s21_sprintf(strr15, "%015d", a8);
  int intDD16 = sprintf(strr16, "%015d", a8);
  ck_assert_str_eq(strr15, strr16);
  ck_assert_int_eq(intDD15, intDD16);

  short int a9 = 123;
  char strr17[100] = {0};
  char strr18[100] = {0};
  int intDD17 = s21_sprintf(strr17, "%+015hd", a9);
  int intDD18 = sprintf(strr18, "%+015hd", a9);
  ck_assert_str_eq(strr17, strr18);
  ck_assert_int_eq(intDD17, intDD18);

  long int a10 = 123;
  char strr19[100] = {0};
  char strr20[100] = {0};
  int intDD19 = s21_sprintf(strr19, "% 015ld", a10);
  int intDD20 = sprintf(strr20, "% 015ld", a10);
  ck_assert_str_eq(strr19, strr20);
  ck_assert_int_eq(intDD19, intDD20);

  int a11 = 0;
  char strr21[100] = {0};
  char strr22[100] = {0};
  int intDD21 = s21_sprintf(strr21, "%+015d", a11);
  int intDD22 = sprintf(strr22, "%+015d", a11);
  ck_assert_str_eq(strr21, strr22);
  ck_assert_int_eq(intDD21, intDD22);
}

START_TEST(s21_sprintf_spec_uTest) {
  unsigned int d1 = 123;
  char str1[100] = {0};
  char str2[100] = {0};
  int intD1 = s21_sprintf(str1, "%u", d1);
  int intD2 = sprintf(str2, "%u", d1);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(intD1, intD2);

  unsigned int d2 = 123;
  char str3[100] = {0};
  char str4[100] = {0};
  int intD3 = s21_sprintf(str3, "%u", d2);
  int intD4 = sprintf(str4, "%u", d2);
  ck_assert_str_eq(str3, str4);
  ck_assert_int_eq(intD3, intD4);

  unsigned int d3 = 123;
  char str5[100] = {0};
  char str6[100] = {0};
  int intD5 = s21_sprintf(str5, "%-u", d3);
  int intD6 = sprintf(str6, "%-u", d3);
  ck_assert_str_eq(str5, str6);
  ck_assert_int_eq(intD5, intD6);

  unsigned int d4 = 123;
  char str7[100] = {0};
  char str8[100] = {0};
  int intD7 = s21_sprintf(str7, "%u", d4);
  int intD8 = sprintf(str8, "%u", d4);
  ck_assert_str_eq(str7, str8);
  ck_assert_int_eq(intD7, intD8);

  unsigned int d5 = 123;
  char str9[100] = {0};
  char str10[100] = {0};
  int intD9 = s21_sprintf(str9, "%u", d5);
  int intD10 = sprintf(str10, "%u", d5);
  ck_assert_str_eq(str9, str10);
  ck_assert_int_eq(intD9, intD10);

  unsigned int a1 = 123;
  char strr1[100] = {0};
  char strr2[100] = {0};
  int intDD1 = s21_sprintf(strr1, "%0u", a1);
  int intDD2 = sprintf(strr2, "%0u", a1);
  ck_assert_str_eq(strr1, strr2);
  ck_assert_int_eq(intDD1, intDD2);

  unsigned long int a2 = 123;
  char strr3[100] = {0};
  char strr4[100] = {0};
  int intDD3 = s21_sprintf(strr3, "%0lu", a2);
  int intDD4 = sprintf(strr4, "%0lu", a2);
  ck_assert_str_eq(strr3, strr4);
  ck_assert_int_eq(intDD3, intDD4);

  unsigned short int a3 = 123;
  char strr5[100] = {0};
  char strr6[100] = {0};
  int intDD5 = s21_sprintf(strr5, "%0hu", a3);
  int intDD6 = sprintf(strr6, "%0hu", a3);
  ck_assert_str_eq(strr5, strr6);
  ck_assert_int_eq(intDD5, intDD6);

  unsigned int a4 = -123;
  char strr7[100] = {0};
  char strr8[100] = {0};
  int intDD7 = s21_sprintf(strr7, "%0d", a4);
  int intDD8 = sprintf(strr8, "%0d", a4);
  ck_assert_str_eq(strr7, strr8);
  ck_assert_int_eq(intDD7, intDD8);

  unsigned int a5 = 123;
  char strr9[100] = {0};
  char strr10[100] = {0};
  int intDD9 = s21_sprintf(strr9, "%.5u", a5);
  int intDD10 = sprintf(strr10, "%.5u", a5);
  ck_assert_str_eq(strr9, strr10);
  ck_assert_int_eq(intDD9, intDD10);

  unsigned int a6 = 123;
  char strr11[100] = {0};
  char strr12[100] = {0};
  int intDD11 = s21_sprintf(strr11, "%15.10u", a6);
  int intDD12 = sprintf(strr12, "%15.10u", a6);
  ck_assert_str_eq(strr11, strr12);
  ck_assert_int_eq(intDD11, intDD12);

  unsigned int a7 = 123;
  char strr13[100] = {0};
  char strr14[100] = {0};
  int intDD13 = s21_sprintf(strr13, "%-15u", a7);
  int intDD14 = sprintf(strr14, "%-15u", a7);
  ck_assert_str_eq(strr13, strr14);
  ck_assert_int_eq(intDD13, intDD14);

  unsigned int a8 = -123;
  char strr15[100] = {0};
  char strr16[100] = {0};
  int intDD15 = s21_sprintf(strr15, "%015u", a8);
  int intDD16 = sprintf(strr16, "%015u", a8);
  ck_assert_str_eq(strr15, strr16);
  ck_assert_int_eq(intDD15, intDD16);

  unsigned short int a9 = 123;
  char strr17[100] = {0};
  char strr18[100] = {0};
  int intDD17 = s21_sprintf(strr17, "%015hu", a9);
  int intDD18 = sprintf(strr18, "%015hu", a9);
  ck_assert_str_eq(strr17, strr18);
  ck_assert_int_eq(intDD17, intDD18);

  unsigned long int a10 = 123;
  char strr19[100] = {0};
  char strr20[100] = {0};
  int intDD19 = s21_sprintf(strr19, "%015lu", a10);
  int intDD20 = sprintf(strr20, "%015lu", a10);
  ck_assert_str_eq(strr19, strr20);
  ck_assert_int_eq(intDD19, intDD20);

  unsigned int a11 = 0;
  char strr21[100] = {0};
  char strr22[100] = {0};
  int intDD21 = s21_sprintf(strr21, "%015u", a11);
  int intDD22 = sprintf(strr22, "%015u", a11);
  ck_assert_str_eq(strr21, strr22);
  ck_assert_int_eq(intDD21, intDD22);
}
END_TEST

START_TEST(s21_sprintf_spec_sTest) {
  char str1[100] = {0};
  char str2[100] = {0};
  s21_sprintf(str1, "%-10s", "Hello, World!");
  sprintf(str2, "%-10s", "Hello, World!");
  ck_assert_str_eq(str1, str2);
  memset(str1, 0, sizeof(str1));
  memset(str2, 0, sizeof(str2));

  s21_sprintf(str1, "%.5s", "Hello, World!");
  sprintf(str2, "%.5s", "Hello, World!");
  ck_assert_str_eq(str1, str2);
  memset(str1, 0, sizeof(str1));
  memset(str2, 0, sizeof(str2));

  s21_sprintf(str1, "%20s", "Hello");
  sprintf(str2, "%20s", "Hello");
  ck_assert_str_eq(str1, str2);
  memset(str1, 0, sizeof(str1));
  memset(str2, 0, sizeof(str2));

  s21_sprintf(str1, "%-20s", "Hello");
  sprintf(str2, "%-20s", "Hello");
  ck_assert_str_eq(str1, str2);
  memset(str1, 0, sizeof(str1));
  memset(str2, 0, sizeof(str2));

  s21_sprintf(str1, "%10.3s", "Hello, World!");
  sprintf(str2, "%10.3s", "Hello, World!");
  ck_assert_str_eq(str1, str2);
  memset(str1, 0, sizeof(str1));
  memset(str2, 0, sizeof(str2));

  s21_sprintf(str1, "%s", "Héllo");
  sprintf(str2, "%s", "Héllo");
  ck_assert_str_eq(str1, str2);
  memset(str1, 0, sizeof(str1));
  memset(str2, 0, sizeof(str2));

  s21_sprintf(str1, "%10.3s", "Hello, World!");
  sprintf(str2, "%10.3s", "Hello, World!");
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_spec_fTest) {
  float d1 = -123.1235;
  char strS1[100] = {0};
  char strD1[100] = {0};
  int intS1 = s21_sprintf(strS1, "%f", d1);
  int intD1 = sprintf(strD1, "%f", d1);
  ck_assert_str_eq(strS1, strD1);
  ck_assert_int_eq(intD1, intS1);
  float d2 = 123.1235764855435340583759843;
  char strS2[100] = {0};
  char strD2[100] = {0};
  int intD2 = s21_sprintf(strS2, "%.45f", d2);
  int intS2 = sprintf(strD2, "%.45f", d2);
  ck_assert_str_eq(strS2, strD2);
  ck_assert_int_eq(intS2, intD2);
  float d3 = 123.99999999;
  char strS3[100] = {0};
  char strD3[100] = {0};
  int intD3 = s21_sprintf(strS3, "%+015f", d3);
  int intS3 = sprintf(strD3, "%+015f", d3);
  ck_assert_str_eq(strS3, strD3);
  ck_assert_int_eq(intS3, intD3);
  float d4 = 123.999999999;
  char strS4[100] = {0};
  char strD4[100] = {0};
  int intD4 = s21_sprintf(strS4, "%010f", d4);
  int intS4 = sprintf(strD4, "%010f", d4);
  ck_assert_str_eq(strS4, strD4);
  ck_assert_int_eq(intS4, intD4);
  float d5 = 123.999999999;
  char strS5[100] = {0};
  char strD5[100] = {0};
  int intD5 = s21_sprintf(strS5, "%#+20.f", d5);
  int intS5 = sprintf(strD5, "%#+20.f", d5);
  ck_assert_str_eq(strS5, strD5);
  ck_assert_int_eq(intS5, intD5);
  long double d6 = 123.999;
  char strS6[100] = {0};
  char strD6[100] = {0};
  int intD6 = s21_sprintf(strS6, "%.45Lf", d6);
  int intS6 = sprintf(strD6, "%.45Lf", d6);
  ck_assert_str_eq(strS6, strD6);
  ck_assert_int_eq(intS6, intD6);
  long double d7 = 123.999953459;
  char strS7[100] = {0};
  char strD7[100] = {0};
  int intD7 = s21_sprintf(strS7, "%#Lf", d7);
  int intS7 = sprintf(strD7, "%#Lf", d7);
  ck_assert_str_eq(strS7, strD7);
  ck_assert_int_eq(intS7, intD7);
  float d8 = 123.5;
  char strS8[100] = {0};
  char strD8[100] = {0};
  int intD8 = s21_sprintf(strS8, "%+.f", d8);
  int intS8 = sprintf(strD8, "%+.f", d8);
  ck_assert_str_eq(strS8, strD8);
  ck_assert_int_eq(intS8, intD8);
  float d9 = 123.5;
  char strS9[100] = {0};
  char strD9[100] = {0};
  int intD9 = s21_sprintf(strS9, "% f", d9);
  int intS9 = sprintf(strD9, "% f", d9);
  ck_assert_str_eq(strS9, strD9);
  ck_assert_int_eq(intS9, intD9);
  float d10 = 123.5;
  char strS10[100] = {0};
  char strD10[100] = {0};
  int intD10 = s21_sprintf(strS10, "% -15.4f", d10);
  int intS10 = sprintf(strD10, "% -15.4f", d10);
  ck_assert_str_eq(strS10, strD10);
  ck_assert_int_eq(intS10, intD10);
}
END_TEST

START_TEST(s21_sprintf_spec_eTest) {
  float float1 = 111.555;
  char lion1[1024] = {0};
  char pudge1[1024] = {0};
  int magnus1 = s21_sprintf(lion1, "%e", float1);
  int magnus2 = sprintf(pudge1, "%e", float1);
  ck_assert_str_eq(lion1, pudge1);
  ck_assert_int_eq(magnus1, magnus2);

  float float2 = 0.00000099999;
  char lion2[1024] = {0};
  char pudge2[1024] = {0};
  int magnus3 = s21_sprintf(lion2, "%.10e", float2);
  int magnus4 = sprintf(pudge2, "%.10e", float2);
  ck_assert_str_eq(lion2, pudge2);
  ck_assert_int_eq(magnus3, magnus4);

  float float3 = -99999999.22;
  char lion3[1024] = {0};
  char pudge3[1024] = {0};
  int magnus5 = s21_sprintf(lion3, "%010e", float3);
  int magnus6 = sprintf(pudge3, "%010e", float3);
  ck_assert_str_eq(lion3, pudge3);
  ck_assert_int_eq(magnus5, magnus6);

  float float4 = 2.55555555;
  char lion4[1024] = {0};
  char pudge4[1024] = {0};
  int magnus7 = s21_sprintf(lion4, "% e", float4);
  int magnus8 = sprintf(pudge4, "% e", float4);
  ck_assert_str_eq(lion4, pudge4);
  ck_assert_int_eq(magnus7, magnus8);

  float float5 = 2.55555555;
  char lion5[1024] = {0};
  char pudge5[1024] = {0};
  int magnus9 = s21_sprintf(lion5, "%+e", float5);
  int magnus10 = sprintf(pudge5, "%+e", float5);
  ck_assert_str_eq(lion5, pudge5);
  ck_assert_int_eq(magnus9, magnus10);

  float float6 = 2.55555555;
  char lion6[1024] = {0};
  char pudge6[1024] = {0};
  int magnus11 = s21_sprintf(lion6, "%-20e", float6);
  int magnus12 = sprintf(pudge6, "%-20e", float6);
  ck_assert_str_eq(lion6, pudge6);
  ck_assert_int_eq(magnus11, magnus12);

  float float7 = -66666.55555555;
  char lion7[1024] = {0};
  char pudge7[1024] = {0};
  int magnus13 = s21_sprintf(lion7, "%20e", float7);
  int magnus14 = sprintf(pudge7, "%20e", float7);
  ck_assert_str_eq(lion7, pudge7);
  ck_assert_int_eq(magnus13, magnus14);

  float float8 = 999999.9;
  char lion8[1024] = {0};
  char pudge8[1024] = {0};
  int magnus15 = s21_sprintf(lion8, "%+015e", float8);
  int magnus16 = sprintf(pudge8, "%+015e", float8);
  ck_assert_str_eq(lion8, pudge8);
  ck_assert_int_eq(magnus15, magnus16);

  float float9 = 0.5;
  char lion9[1024] = {0};
  char pudge9[1024] = {0};
  int magnus17 = s21_sprintf(lion9, "%.e", float9);
  int magnus18 = sprintf(pudge9, "%.e", float9);
  ck_assert_str_eq(lion9, pudge9);
  ck_assert_int_eq(magnus17, magnus18);

  float float10 = 0.5;
  char lion10[1024] = {0};
  char pudge10[1024] = {0};
  int magnus19 = s21_sprintf(lion10, "%.E", float10);
  int magnus20 = sprintf(pudge10, "%.E", float10);
  ck_assert_str_eq(lion10, pudge10);
  ck_assert_int_eq(magnus19, magnus20);
}
END_TEST

START_TEST(s21_strerrorTest) {
  int i = 0;
  while (i < 500) {
    char *ggg = strerror(i);
    char *ggg2 = s21_strerror(i);
    ck_assert_str_eq(ggg, ggg2);
    i++;
  }
}
END_TEST

START_TEST(s21_sscanf_spec_allTest) {
  char *buff = "   123 123ab hihihaha sanya";
  char str[100] = {0};
  char name;
  int age = 10;
  char name2;
  int age2 = 10;
  char str2[100] = {0};
  s21_sscanf(buff, "%*d%2d%*c%c%*s%2s", &age, &name, str);
  sscanf(buff, "%*d%2d%*c%c%*s%2s", &age2, &name2, str2);
  ck_assert_str_eq(str, str2);
  ck_assert_int_eq(name, name2);
  ck_assert_int_eq(age, age2);

  char *buff1 = "   123 123ab 2398 10fF 10FfHASD";
  int u1 = 10;
  int u2 = 10;
  int o1 = 10;
  int o2 = 10;
  int x1 = 10;
  int x2 = 10;
  s21_sscanf(buff1, "%*u%3u%*o%4o%*x%X", &u1, &o1, &x1);
  sscanf(buff1, "%*u%3u%*o%4o%*x%X", &u2, &o2, &x2);
  ck_assert_int_eq(u1, u2);
  ck_assert_int_eq(o1, o2);
  ck_assert_int_eq(x1, x2);

  char *buff2 = "ab   123 123 10fF";
  unsigned long int u3 = 10;
  unsigned long int u4 = 10;
  unsigned long int o3 = 10;
  unsigned long int o4 = 10;
  unsigned long int x3 = 10;
  unsigned long int x4 = 10;
  s21_sscanf(buff2, "ab   %3lu%2lo%lX", &u3, &o3, &x3);
  sscanf(buff2, "ab   %3lu%2lo%lX", &u4, &o4, &x4);
  ck_assert_int_eq(u3, u4);
  ck_assert_int_eq(o3, o4);
  ck_assert_int_eq(x3, x4);
  char *buff3 = "ab   +888 5 90 44 1Ff";
  long int li1 = 10;
  long int li2 = 10;
  short int si1 = 10;
  short int si2 = 10;
  unsigned short int u5 = 10;
  unsigned short int u6 = 10;
  unsigned short int o5 = 10;
  unsigned short int o6 = 10;
  unsigned short int x5 = 10;
  unsigned short int x6 = 10;
  s21_sscanf(buff3, "ab   %ld %hd %hu %ho %hX", &li1, &si1, &u5, &o5, &x5);
  sscanf(buff3, "ab   %ld %hd %hu %ho %hX", &li2, &si2, &u6, &o6, &x6);
  ck_assert_int_eq(u5, u6);
  ck_assert_int_eq(o5, o6);
  ck_assert_int_eq(x5, x6);
  ck_assert_int_eq(li1, li2);
  ck_assert_int_eq(si1, si2);

  char *buff4 = "ab   -888 5 123 44 1Ff";
  int si3 = 10;
  int si4 = 10;
  int u7 = 10;
  int u8 = 10;
  int o7 = 10;
  int o8 = 10;
  int x7 = 10;
  int x8 = 10;
  s21_sscanf(buff4, "ab   %d %u %o %X", &si3, &u7, &o7, &x7);
  sscanf(buff4, "ab   %d %u %o %X", &si4, &u8, &o8, &x8);
  ck_assert_int_eq(u7, u8);
  ck_assert_int_eq(o7, o8);
  ck_assert_int_eq(x7, x8);

  char *buff5 = "ab   10F 11AF 4a 5B";
  unsigned long int lx1 = 10;
  unsigned long int lx2 = 10;
  unsigned short int sx1 = 10;
  unsigned short int sx2 = 10;
  unsigned int dx1 = 10;
  unsigned int dx2 = 10;
  s21_sscanf(buff5, "ab   %lx %hx %*x %x", &lx1, &sx1, &dx1);
  sscanf(buff5, "ab   %lx %hx %*x %x", &lx2, &sx2, &dx2);
  ck_assert_int_eq(lx1, lx2);
  ck_assert_int_eq(sx1, sx2);
  ck_assert_int_eq(dx1, dx2);
}

START_TEST(s21_sscanf_spec_f_e_E_g_ETest) {
  const char *temp = "284.987654321 284.987654321 284.987654321";
  float fres1;
  float fres2;
  double dres1;
  double dres2;
  long double ldres1;
  long double ldres2;
  s21_sscanf(temp, "%f %lf %Lf", &fres1, &dres1, &ldres1);
  sscanf(temp, "%f %lf %Lf", &fres2, &dres2, &ldres2);
  ck_assert_float_eq(fres1, fres2);
  ck_assert_double_eq(dres1, dres2);
  ck_assert_ldouble_eq(ldres1, ldres2);
  const char *temp2 = "284.23408 284.23408 284.23408";
  float fres3;
  float fres4;
  double dres3;
  double dres4;
  long double ldres3;
  long double ldres4;
  s21_sscanf(temp2, "%e %le %Le", &fres3, &dres3, &ldres3);
  sscanf(temp2, "%e %le %Le", &fres4, &dres4, &ldres4);
  ck_assert_float_eq(fres3, fres4);
  ck_assert_double_eq(dres3, dres4);
  ck_assert_ldouble_eq(ldres3, ldres4);
  const char *temp3 = "284.23408 284.23408 284.23408";
  float fres5;
  float fres6;
  double dres5;
  double dres6;
  long double ldres5;
  long double ldres6;
  s21_sscanf(temp3, "%g %lg %Lg", &fres5, &dres5, &ldres5);
  sscanf(temp3, "%g %lg %Lg", &fres6, &dres6, &ldres6);
  ck_assert_float_eq(fres5, fres6);
  ck_assert_double_eq(dres5, dres6);
  ck_assert_ldouble_eq(ldres5, ldres6);
  float fres7;
  float fres8;
  double dres7;
  double dres8;
  long double ldres7;
  long double ldres8;
  s21_sscanf(temp3, "%G %lG %LG", &fres7, &dres7, &ldres7);
  sscanf(temp3, "%G %lG %LG", &fres8, &dres8, &ldres8);
  ck_assert_float_eq(fres7, fres8);
  ck_assert_double_eq(dres7, dres8);
  ck_assert_ldouble_eq(ldres7, ldres8);

  s21_sscanf(temp2, "%E %lE %LE", &fres3, &dres3, &ldres3);
  sscanf(temp2, "%E %lE %LE", &fres4, &dres4, &ldres4);
  ck_assert_float_eq(fres3, fres4);
  ck_assert_double_eq(dres3, dres4);
  ck_assert_ldouble_eq(ldres3, ldres4);
}

int main(void) {
  Suite *s1 = suite_create("s21_string");
  TCase *t1 = tcase_create("s21_string");
  SRunner *run = srunner_create(s1);
  int number_failed;
  suite_add_tcase(s1, t1);
  tcase_add_test(t1, s21_memcpyTest);
  tcase_add_test(t1, s21_memsetTest);
  tcase_add_test(t1, s21_strncpyTest);
  tcase_add_test(t1, s21_strncatTest);
  tcase_add_test(t1, s21_strlenTest);
  tcase_add_test(t1, s21_strcspnTest);
  tcase_add_test(t1, s21_strtokTest);
  tcase_add_test(t1, s21_to_upperTest);
  tcase_add_test(t1, s21_insertTest);
  tcase_add_test(t1, s21_memcmpTest);
  tcase_add_test(t1, s21_strncmpTest);
  tcase_add_test(t1, s21_to_lowerTest);
  tcase_add_test(t1, s21_strstrTest);
  tcase_add_test(t1, s21_strpbrkTest);
  tcase_add_test(t1, s21_trimTest);
  tcase_add_test(t1, s21_memchrTest);
  tcase_add_test(t1, s21_strchrTest);
  tcase_add_test(t1, s21_strrchrTest);
  tcase_add_test(t1, s21_sprintf_spec_pTest);
  tcase_add_test(t1, s21_sprintf_spec_oTest);
  tcase_add_test(t1, s21_sprintf_spec_x_XTest);
  tcase_add_test(t1, s21_sprintf_spec_cTest);
  tcase_add_test(t1, s21_sprintf_spec_dTest);
  tcase_add_test(t1, s21_sprintf_spec_uTest);
  tcase_add_test(t1, s21_sprintf_spec_sTest);
  tcase_add_test(t1, s21_sprintf_spec_fTest);
  tcase_add_test(t1, s21_sscanf_spec_allTest);
  tcase_add_test(t1, s21_sprintf_spec_eTest);
  tcase_add_test(t1, s21_sscanf_spec_f_e_E_g_ETest);
  tcase_add_test(t1, s21_strerrorTest);
  srunner_run_all(run, CK_NORMAL);
  number_failed = srunner_ntests_failed(run);
  srunner_free(run);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
