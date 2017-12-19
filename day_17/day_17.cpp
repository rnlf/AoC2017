#include <cstdint>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include "../timer.h"


uint32_t part2(uint32_t input) {
  int pos = 0;
  uint32_t cur;
  for(uint32_t i = 1; i < 50000001; ++i) {
    pos = (pos + input) % i;
    if(pos == 0) {
      cur = i;
    }
    ++pos;
  }
  return cur;
}

int main(int argc, char ** argv) {
  int input = std::atoi(argv[1]);

  // part 1 lost to editing before committing. Who cares :)
  
  auto res = measure_time(10, part2, input);
  printf("%u\n", res[0]);
}
