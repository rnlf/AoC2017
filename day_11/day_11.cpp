#include <algorithm>
#include <cstdint>
#include <cstdio>

uint16_t
constexpr make_dir(uint8_t a, uint8_t b) {
  return a << 8 | b;
}


int
constexpr distance(int x, int y) {
  return std::max(abs(x+y), std::max(abs(x), abs(y)));
}


int main(int argc, char **argv) {
  FILE *f = fopen(argv[1], "r");

  int x = 0;
  int y = 0;
  int maxd = 0;

  for(;;) {
    char buf[3];
    fscanf(f, "%[a-z]", buf);
    uint16_t dir = make_dir(buf[0], buf[1]);

    switch(dir) {
    case make_dir('n', 0):
      --x;
      ++y;
      break;

    case make_dir('n', 'e'):
      ++y;
      break;

    case make_dir('s', 'e'):
      ++x;
      break;

    case make_dir('s', 0):
      ++x;
      --y;
      break;

    case make_dir('s', 'w'):
      --y;
      break;

    case make_dir('n', 'w'):
      --x;
      break;
    }

    int c = fgetc(f);
    if(c != ',') {
      break;
    }

    maxd = std::max(maxd, distance(x, y));
  }

  fclose(f);

  printf("%d, %d, %d\n", x, y, distance(x, y));
  printf("%d\n", maxd);
}
