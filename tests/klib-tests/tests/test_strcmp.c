#include "trap.h"

int main() {
  check(strcmp("", "") == 0, 1);       /* Trivial case. */
  check(strcmp("a", "a") == 0, 2);     /* Identity. */
  check(strcmp("abc", "abc") == 0, 3); /* Multicharacter. */
  check(strcmp("abc", "abcd") < 0, 4); /* Length mismatches. */
  check(strcmp("abcd", "abc") > 0, 5);
  check(strcmp("abcd", "abce") < 0, 6); /* Honest miscompares. */
  check(strcmp("abce", "abcd") > 0, 7);
  check(strcmp("a\203", "a") > 0, 8); /* Tricky if char signed. */
  check(strcmp("a\203", "a\003") > 0, 9);

  {
    char buf1[0x40], buf2[0x40];
    int i, j;
    for (i = 0; i < 0x10; i++)
      for (j = 0; j < 0x10; j++) {
        int k;
        for (k = 0; k < 0x3f; k++) {
          buf1[k] = '0' ^ (k & 4);
          buf2[k] = '4' ^ (k & 4);
        }
        buf1[i] = buf1[0x3f] = 0;
        buf2[j] = buf2[0x3f] = 0;
        for (k = 0; k < 0xf; k++) {
          int cnum = 0x10 + 0x10 * k + 0x100 * j + 0x1000 * i;
          check(strcmp(buf1 + i, buf2 + j) == 0, cnum);
          buf1[i + k] = 'A' + i + k;
          buf1[i + k + 1] = 0;
          check(strcmp(buf1 + i, buf2 + j) > 0, cnum + 1);
          check(strcmp(buf2 + j, buf1 + i) < 0, cnum + 2);
          buf2[j + k] = 'B' + i + k;
          buf2[j + k + 1] = 0;
          check(strcmp(buf1 + i, buf2 + j) < 0, cnum + 3);
          check(strcmp(buf2 + j, buf1 + i) > 0, cnum + 4);
          buf2[j + k] = 'A' + i + k;
          buf1[i] = 'A' + i + 0x80;
          check(strcmp(buf1 + i, buf2 + j) > 0, cnum + 5);
          check(strcmp(buf2 + j, buf1 + i) < 0, cnum + 6);
          buf1[i] = 'A' + i;
        }
      }
  }
  return 0;
}
