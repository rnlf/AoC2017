#include <vector>
#include <string>
#include "../timer.h"
#include "../fileread.h"


unsigned filter(unsigned a, unsigned b) {
  return !(a^b) * (a-unsigned('0'));
}

unsigned run(char const* filename) {
  auto data = read_file(filename);
  unsigned size = data.size();
  while(data[size-1] == '\n') {
    --size;
  }

  #ifdef PART2
    unsigned const offset = size / 2;
  #else
    unsigned const offset = 1;
  #endif
  
  unsigned const end = size - offset;

  unsigned sum = 0;
  for(int i = 0; i < end; ++i) {
    sum += filter(data[i], data[i+offset]);
  }

  #ifdef PART2
    sum <<= 1;
  #else
    sum += filter(data[size-1], data[0]);
  #endif

  return sum;
}


int main(int argc, char** argv) {
  auto results = measure_time(1000, run, argv[1]);
  printf("%u\n", results[0]);
}
