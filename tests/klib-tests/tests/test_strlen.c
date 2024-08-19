#include "trap.h"
#include <limits.h>

static void
do_test(size_t align, size_t len) {
  size_t i;

  align &= 63;
  if (align + sizeof(char) * len >= ARRAY_MAX_LEN) {
    return;
  }

  char *buf = one;

  for (i = 0; i < len; ++i) {
    buf[align + i] = 1;
  }
  buf[align + len] = 0;

  check(strlen((char *)(buf + align)) == len);
}

int main() {
  for (int i = 1; i < 8; ++i) {
    do_test(sizeof(char) * i, i);
    do_test(0, i);
  }
  for (int i = 2; i <= 12; ++i) {
    do_test(0, 1 << i);
    do_test(sizeof(char) * 7, 1 << i);
    do_test(sizeof(char) * i, 1 << i);
    do_test(sizeof(char) * i, (size_t)((1 << i) / 3));
  }
  return 0;
}
