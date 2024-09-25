#include "trap.h"

int main() {
  check(strncmp("", "", 99) == 0, 1);       /* Trivial case. */
  check(strncmp("a", "a", 99) == 0, 2);     /* Identity. */
  check(strncmp("abc", "abc", 99) == 0, 3); /* Multicharacter. */
  check(strncmp("abc", "abcd", 99) < 0, 4); /* Length unequal. */
  check(strncmp("abcd", "abc", 99) > 0, 5);
  check(strncmp("abcd", "abce", 99) < 0, 6); /* Honestly unequal. */
  check(strncmp("abce", "abcd", 99) > 0, 7);
  check(strncmp("a\203", "a", 2) > 0, 8); /* Tricky if '\203' < 0 */
  check(strncmp("a\203", "a\003", 2) > 0, 9);
  check(strncmp("abce", "abcd", 3) == 0, 10);    /* Count limited. */
  check(strncmp("abce", "abc", 3) == 0, 11);     /* Count == length. */
  check(strncmp("abcd", "abce", 4) < 0, 12);     /* Nudging limit. */
  check(strncmp("abc", "def", 0) == 0, 13);      /* Zero count. */
  check(strncmp("abc", "", (size_t)-1) > 0, 14); /* set sign bit in count */
  check(strncmp("abc", "abc", (size_t)-2) == 0, 15);
  return 0;
}
