#include "trap.h"
#include <limits.h>
int main(int argc, char const *argv[]) {
  char *p = one;

  // test int
  int data[] = {0, INT_MAX / 17, INT_MAX, INT_MIN, INT_MIN + 1,
                UINT_MAX / 17, INT_MAX / 17, UINT_MAX};
  for (int i = 0; i < 8; i++) {
    int written_number = sprintf(p, "%d ", data[i]);
    check(written_number != 0);
    p += written_number;
  }

  // test char / string
  int written_number = sprintf(p, "%s %c %s %%csd\n", "the", '\203', "end");
  check(written_number != 0);

  equal(one, "0 126322567 2147483647 -2147483648 -2147483647 252645135 126322567 -1 the \203 end \%csd\n");
  return 0;
}
