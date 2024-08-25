#include <am.h>
#include <klib-macros.h>
#include <stdio.h>

int main(const char *args) {
  const char *fmt =
      "Hello, AbstractMachine!\n"
      "mainargs = '%'.\n";

  for (const char *p = fmt; *p; p++) {
    (*p == '%') ? putstr(args) : putch(*p);
  }

  printf("%p %x %s\n", -1, 0xFA, fmt);
  return 0;
}