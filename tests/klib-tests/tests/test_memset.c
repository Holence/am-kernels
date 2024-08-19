#include "trap.h"

#define N 32
uint8_t data[N];

void reset() {
  int i;
  for (i = 0; i < N; i++) {
    data[i] = i + 1;
  }
}

// 检查[l,r)区间中的值是否依次为val, val + 1, val + 2...
void check_seq(int l, int r, int val) {
  int i;
  for (i = l; i < r; i++) {
    check(data[i] == val + i - l);
  }
}

// 检查[l,r)区间中的值是否均为val
void check_eq(int l, int r, int val) {
  int i;
  for (i = l; i < r; i++) {
    check(data[i] == val);
  }
}

int main() {
  int l, r;
  for (l = 0; l < N; l++) {
    for (r = l + 1; r <= N; r++) {
      reset();
      uint8_t val = (l + r) / 2;
      memset(data + l, val, r - l);
      check_seq(0, l, 1);
      check_eq(l, r, val);
      check_seq(r, N, r + 1);
    }
  }

  (void)strcpy(one, "abcdefgh");
  check(memset(one + 1, 'x', 3) == one + 1, 1); /* Return value. */
  equal(one, "axxxefgh", 2);                    /* Basic test. */

  (void)memset(one + 2, 'y', 0);
  equal(one, "axxxefgh", 3); /* Zero-length set. */

  (void)memset(one + 5, 0, 1);
  equal(one, "axxxe", 4);  /* Zero fill. */
  equal(one + 6, "gh", 5); /* And the leftover. */

  (void)memset(one + 2, 010045, 1);
  equal(one, "ax\045xe", 6); /* Unsigned char convert. */

  /* Non-8bit fill character.  */
  memset(one, 0x101, sizeof(one));
  for (int i = 0; i < (int)sizeof(one); ++i)
    check(one[i] == '\01', 7);

  /* Test for more complex versions of memset, for all alignments and
     lengths up to 256. This test takes a little while, perhaps it should
     be made weaker?  */
  {
    int i;
    int j;
    int k;
    int c;

    for (i = 0; i < N; i++)
      data[i] = 'x';
    for (c = 0; c <= 'y'; c += 'y') /* check for memset(,0,) and
                                       memset(,'y',) */
      for (j = 0; j < N / 2; j++)
        for (i = 0; i < N / 2; i++) {
          memset(data + i, c, j);
          for (k = 0; k < i; k++)
            check(data[k] == 'x');
          for (k = i; k < i + j; k++) {
            check(data[k] == c);
            data[k] = 'x';
          }
          for (k = i + j; k < N; k++)
            check(data[k] == 'x');
          continue;
        }
  }

  return 0;
}