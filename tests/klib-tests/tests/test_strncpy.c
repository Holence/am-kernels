#include "trap.h"

int main() {
  check(strncpy(one, "abc", 4) == one, 1); /* Returned value. */
  equal(one, "abc", 2);                    /* Did the copy go right? */

  (void)strcpy(one, "abcdefgh");
  (void)strncpy(one, "xyz", 2);
  equal(one, "xycdefgh", 3); /* Copy cut by count. */

  (void)strcpy(one, "abcdefgh");
  (void)strncpy(one, "xyz", 3); /* Copy cut just before NUL. */
  equal(one, "xyzdefgh", 4);

  (void)strcpy(one, "abcdefgh");
  (void)strncpy(one, "xyz", 4); /* Copy just includes NUL. */
  equal(one, "xyz", 5);
  equal(one + 4, "efgh", 6); /* Wrote too much? */

  (void)strcpy(one, "abcdefgh");
  (void)strncpy(one, "xyz", 5); /* Copy includes padding. */
  equal(one, "xyz", 7);
  equal(one + 4, "", 8);
  equal(one + 5, "fgh", 9);

  (void)strcpy(one, "abc");
  (void)strncpy(one, "xyz", 0); /* Zero-length copy. */
  equal(one, "abc", 10);

  (void)strncpy(one, "", 2); /* Zero-length source. */
  equal(one, "", 11);
  equal(one + 1, "", 12);
  equal(one + 2, "c", 13);

  (void)strcpy(one, "hi there");
  (void)strncpy(two, one, 9);
  equal(two, "hi there", 14); /* Just paranoia. */
  equal(one, "hi there", 15); /* Stomped on source? */
  return 0;
}