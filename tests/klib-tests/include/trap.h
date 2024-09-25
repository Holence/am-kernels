#ifndef __TRAP_H__
#define __TRAP_H__

#include <am.h>
#include <klib.h>
#include <klib-macros.h>

__attribute__((noinline)) void check(bool cond, ...) {
  // 后面跟着的那个数字，是原测试集中附带的，在我这里没用的
  if (!cond)
    halt(1);
}

#define ARRAY_MAX_LEN 1024
char one[ARRAY_MAX_LEN];
char two[ARRAY_MAX_LEN];

// 后面跟着的那个数字，是原测试集中附带的，在我这里没用的
#define equal(char_a, char_b, ...) check(strcmp(char_a, char_b) == 0);

#endif
