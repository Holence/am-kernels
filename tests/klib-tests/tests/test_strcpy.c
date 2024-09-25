#include "trap.h"

#define SIMPLE_COPY(fn, n, str, ntest)            \
  do {                                            \
    int __n;                                      \
    char *cp;                                     \
    for (__n = 0; __n < (int)sizeof(one); ++__n)  \
      one[__n] = 'Z';                             \
    fn(one, str);                                 \
    for (cp = one, __n = 0; __n < n; ++__n, ++cp) \
      check(*cp == '0' + (n % 10), ntest);        \
    check(*cp == '\0', ntest);                    \
  } while (0)

int main() {
  check(strcpy(one, "abcd") == one, 1); /* Returned value. */
  equal(one, "abcd", 2);                /* Basic test. */

  (void)strcpy(one, "x");
  equal(one, "x", 3);      /* Writeover. */
  equal(one + 2, "cd", 4); /* Wrote too much? */

  (void)strcpy(two, "hi there");
  (void)strcpy(one, two);
  equal(one, "hi there", 5); /* Basic test encore. */
  equal(two, "hi there", 6); /* Stomped on source? */

  (void)strcpy(one, "");
  equal(one, "", 7); /* Boundary condition. */

  for (int i = 0; i < 16; i++) {
    (void)strcpy(one + i, "hi there"); /* Unaligned destination. */
    equal(one + i, "hi there", 8 + (i * 2));
    (void)strcpy(two, one + i); /* Unaligned source. */
    equal(two, "hi there", 9 + (i * 2));
  }

  SIMPLE_COPY(strcpy, 0, "", 41);
  SIMPLE_COPY(strcpy, 1, "1", 42);
  SIMPLE_COPY(strcpy, 2, "22", 43);
  SIMPLE_COPY(strcpy, 3, "333", 44);
  SIMPLE_COPY(strcpy, 4, "4444", 45);
  SIMPLE_COPY(strcpy, 5, "55555", 46);
  SIMPLE_COPY(strcpy, 6, "666666", 47);
  SIMPLE_COPY(strcpy, 7, "7777777", 48);
  SIMPLE_COPY(strcpy, 8, "88888888", 49);
  SIMPLE_COPY(strcpy, 9, "999999999", 50);
  SIMPLE_COPY(strcpy, 10, "0000000000", 51);
  SIMPLE_COPY(strcpy, 11, "11111111111", 52);
  SIMPLE_COPY(strcpy, 12, "222222222222", 53);
  SIMPLE_COPY(strcpy, 13, "3333333333333", 54);
  SIMPLE_COPY(strcpy, 14, "44444444444444", 55);
  SIMPLE_COPY(strcpy, 15, "555555555555555", 56);
  SIMPLE_COPY(strcpy, 16, "6666666666666666", 57);

  /* Simple test using implicitly coerced `void *' arguments.  */
  const void *src = "frobozz";
  void *dst = one;
  check(strcpy(dst, src) == dst, 1);
  equal(dst, "frobozz", 2);

  return 0;
}