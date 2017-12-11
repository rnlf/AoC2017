#include <vector>
#include <cstdio>
#include <cstdint>

void process(uint8_t *data, unsigned pos, unsigned len) {
  for(unsigned i = 0; i < len / 2; ++i) {
    unsigned i1 = (pos + i) % 256;
    unsigned i2 = (pos + len - i - 1) % 256;
    uint8_t tmp = data[i1];
    data[i1] = data[i2];
    data[i2] = tmp;
  }
}


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

  dat.push_back(17);
  dat.push_back(31);
  dat.push_back(73);
  dat.push_back(47);
  dat.push_back(23);

  return dat;
}
#endif


int main(int argc, char ** argv) {

  uint8_t data[256];
  for(unsigned i = 0; i < 256; ++i) {
    data[i] = uint8_t(i);
  }

  unsigned pos = 0;
  unsigned skip = 0;

  auto input = read_input(argv[1]);

  #ifdef PART2
    for(int turn = 0; turn < 64; ++turn) {
  #endif

      for(auto const len: input) {
        process(data, pos, len);
        pos = (pos + skip + len) % 256;
        ++skip;
      }

  #ifdef PART2
    }
  #endif

  #ifdef PART2
    for(int i=0; i < 16; ++i) {
      uint8_t d = 0;
      for(int k = 0; k < 16; ++k) {
        d ^= data[16*i+k];
      }
      printf("%02x", d);
    }
  #else
    printf("%u\n", unsigned(data[0]) * unsigned(data[1]));
  #endif
}
