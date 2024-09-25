#include "trap.h"

int main() {
  int cnt = 0;
  check(memcmp("a", "a", 1) == 0, cnt++);      /* Identity. */
  check(memcmp("abc", "abc", 3) == 0, cnt++);  /* Multicharacter. */
  check(memcmp("abcd", "abcf", 4) < 0, cnt++); /* Honestly unequal. */
  check(memcmp("abcf", "abcd", 4) > 0, cnt++);
  check(memcmp("alph", "cold", 4) < 0, cnt++);
  check(memcmp("a\203", "a\003", 2) > 0, cnt++);
  check(memcmp("a\003", "a\203", 2) < 0, cnt++);
  check(memcmp("a\003bc", "a\203bc", 2) < 0, cnt++);
  check(memcmp("abc\203", "abc\003", 4) > 0, cnt++);
  check(memcmp("abc\003", "abc\203", 4) < 0, cnt++);
  check(memcmp("abcf", "abcd", 3) == 0, cnt++); /* Count limited. */
  check(memcmp("abc", "def", 0) == 0, cnt++);   /* Zero count. */
  /* Comparisons with shifting 4-byte boundaries. */
  for (int i = 0; i < 4; ++i) {
    char *a = one + i;
    char *b = two + i;
    strncpy(a, "--------11112222", 16);
    strncpy(b, "--------33334444", 16);
    check(memcmp(b, a, 16) > 0, cnt++);
    check(memcmp(a, b, 16) < 0, cnt++);
  }
  return 0;
}