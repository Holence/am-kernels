#include "trap.h"

int main() {
  (void)strcpy(one, "ijk");
  check(strcat(one, "lmn") == one, 1); /* Returned value. */
  equal(one, "ijklmn", 2);             /* Basic test. */

  (void)strcpy(one, "x");
  (void)strcat(one, "yz");
  equal(one, "xyz", 3);    /* Writeover. */
  equal(one + 4, "mn", 4); /* Wrote too much? */

  (void)strcpy(one, "gh");
  (void)strcpy(two, "ef");
  (void)strcat(one, two);
  equal(one, "ghef", 5); /* Basic test encore. */
  equal(two, "ef", 6);   /* Stomped on source? */

  (void)strcpy(one, "");
  (void)strcat(one, "");
  equal(one, "", 7); /* Boundary conditions. */
  (void)strcpy(one, "ab");
  (void)strcat(one, "");
  equal(one, "ab", 8);
  (void)strcpy(one, "");
  (void)strcat(one, "cd");
  equal(one, "cd", 9);

  // 大概要跑50多秒
  int ntest = 10;
  char buf1[80] __attribute__((aligned(16)));
  char buf2[32] __attribute__((aligned(16)));
  for (size_t n1 = 0; n1 < 16; ++n1)
    for (size_t n2 = 0; n2 < 16; ++n2)
      for (size_t n3 = 0; n3 < 32; ++n3) {

        memset(buf1, 'b', sizeof(buf1));

        memset(buf1 + n2, 'a', n3);
        buf1[n2 + n3] = '\0';
        strcpy(buf2 + n1, "123");

        check(strcat(buf1 + n2, buf2 + n1) == buf1 + n2, ntest);
        for (size_t i = 0; i < sizeof(buf1); ++i) {
          if (i < n2)
            check(buf1[i] == 'b', ntest);
          else if (i < n2 + n3)
            check(buf1[i] == 'a', ntest);
          else if (i < n2 + n3 + 3)
            check(buf1[i] == "123"[i - (n2 + n3)], ntest);
          else if (i == n2 + n3 + 3)
            check(buf1[i] == '\0', ntest);
          else
            check(buf1[i] == 'b', ntest);
        }
      }
  return 0;
}
