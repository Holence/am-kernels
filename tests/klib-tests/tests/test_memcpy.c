#include "trap.h"

int main() {
  check(memcpy(one, "abc", 4) == one, 1); /* Returned value. */
  equal(one, "abc", 2);                   /* Did the copy go right? */

  (void)strcpy(one, "abcdefgh");
  (void)memcpy(one + 1, "xyz", 2);
  equal(one, "axydefgh", 3); /* Basic test. */

  (void)strcpy(one, "abc");
  (void)memcpy(one, "xyz", 0);
  equal(one, "abc", 4); /* Zero-length copy. */

  (void)strcpy(one, "hi there");
  (void)strcpy(two, "foo");
  (void)memcpy(two, one, 9);
  equal(two, "hi there", 5); /* Just paranoia. */
  equal(one, "hi there", 6); /* Stomped on source? */

  for (int i = 0; i < 16; i++) {
    const char *x = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
    strcpy(one, x);
    check(memcpy(one + i, "hi there", 9) == one + i,
          7 + (i * 6));                         /* Unaligned destination. */
    check(memcmp(one, x, i) == 0, 8 + (i * 6)); /* Wrote under? */
    equal(one + i, "hi there", 9 + (i * 6));
    check(one[i + 9] == 'x', 10 + (i * 6)); /* Wrote over? */
    check(memcpy(two, one + i, 9) == two,
          11 + (i * 6)); /* Unaligned source. */
    equal(two, "hi there", 12 + (i * 6));
  }
  return 0;
}