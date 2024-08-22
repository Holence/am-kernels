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

  printf("%d %s %s\n", 114514, fmt, args);
  return 0;
}
