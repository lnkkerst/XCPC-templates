#include <cctype>
#include <cstdio>

namespace IO {
const int MAXSIZE = 1 << 20;
char buf[MAXSIZE], *p1, *p2;
#define gc()                                                                   \
  (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, MAXSIZE, stdin), p1 == p2)     \
       ? EOF                                                                   \
       : *p1++)

int rd() {
  int x = 0, f = 1;
  char c = gc();
  while (!isdigit(c)) {
    if (c == '-') {
      f = -1;
    }
    c = gc();
  }
  while (isdigit(c)) {
    x = x * 10 + (c ^ 48), c = gc();
  }
  return x * f;
}

char pbuf[1 << 20], *pp = pbuf;

void push(const char &c) {
  if (pp - pbuf == 1 << 20) {
    fwrite(pbuf, 1, 1 << 20, stdout), pp = pbuf;
  }
  *pp++ = c;
}

void write(int x) {
  static int sta[35];
  int top = 0;
  do {
    sta[top++] = x % 10, x /= 10;
  } while (x);
  while (top) {
    push(sta[--top] + '0');
  }
}
} // namespace IO
