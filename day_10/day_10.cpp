#include <vector>
#include <cstdio>
#include <cstdint>

#include "knot_hash.h"


#ifndef PART2
std::vector<uint8_t> read_input(char const* filename) {
  FILE* f = fopen(filename, "r");
  std::vector<uint8_t> dat;

  for(;;) {
    unsigned len;
    fscanf(f, "%u", &len);
    dat.push_back(len);
    int c = fgetc(f);
    if(c != ',') {
      break;
    }
  }

  fclose(f);
  return dat;
}
#else
std::vector<uint8_t> read_input(char const* filename) {
  FILE* f = fopen(filename, "r");
  std::vector<uint8_t> dat;

  for(;;) {
    int c = fgetc(f);
    if(c == '\n') {
      break;
    }

    dat.push_back(c);
  }

  fclose(f);

  return dat;
}
#endif


int main(int argc, char ** argv) {


  auto input = read_input(argv[1]);

  #ifndef PART2
    uint8_t data[256];
    unsigned pos = 0;
    unsigned skip =0;
    for(unsigned i = 0; i < 256; ++i) {
      data[i] = uint8_t(i);
    }
    for(auto const len: input) {
      process(data, pos, len);
      pos = (pos + skip + len) % 256;
      ++skip;
    }
    printf("%u\n", unsigned(data[0]) * unsigned(data[1]));
  #else
    KnotHash hash = knot_hash(input);
    for(int i = 0; i < 16; ++i) {
      printf("%02x", hash.data[i]);
    }
    printf("\n");
  #endif
}
