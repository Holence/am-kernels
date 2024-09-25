#include "trap.h"
#include <stdint.h>
int main(int argc, char const *argv[]) {
  //   asm("addi a0, x0, 0\n"
  //       "addi a0, a0, 0xf0\n"
  //       "addi sp, sp, -4\n"
  //       "sb a0, (sp)\n"
  //       "lb a1, (sp)\n"
  //       "addi sp, sp, 4\n");
  int8_t data[2] = {0xf0, 0xf};
  int8_t *p = data;
  int ans[] = {256, -240, -240, 225};
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      check(ans[i * 2 + j] == (int)(*(p + i)) * (int)(*(p + j)));
    }
  }
  return 0;
}