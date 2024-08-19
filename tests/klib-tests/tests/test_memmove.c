#include "trap.h"

int main() {
  check(memmove(one, "abc", 4) == one, 1); /* Returned value. */
  equal(one, "abc", 2);                    /* Did the copy go right? */

  (void)strcpy(one, "abcdefgh");
  (void)memmove(one + 1, "xyz", 2);
  equal(one, "axydefgh", 3); /* Basic test. */

  (void)strcpy(one, "abc");
  (void)memmove(one, "xyz", 0);
  equal(one, "abc", 4); /* Zero-length copy. */

  (void)strcpy(one, "hi there");
  (void)strcpy(two, "foo");
  (void)memmove(two, one, 9);
  equal(two, "hi there", 5); /* Just paranoia. */
  equal(one, "hi there", 6); /* Stomped on source? */

  (void)strcpy(one, "abcdefgh");
  (void)memmove(one + 1, one, 9);
  equal(one, "aabcdefgh", 7); /* Overlap, right-to-left. */

  (void)strcpy(one, "abcdefgh");
  (void)memmove(one + 1, one + 2, 7);
  equal(one, "acdefgh", 8); /* Overlap, left-to-right. */

  // (void)strcpy(one, "abcdefgh");
  // (void)memmove(one, one, 9);
  // equal(one, "abcdefgh", 9); /* 100% overlap. */
  return 0;
}