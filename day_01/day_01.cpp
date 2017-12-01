#include <vector>
#include <string>
#include "../timer.h"
#include "../fileread.h"


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
  
  unsigned sum = 0;
  for(int i = 0; i < size; ++i) {
    if(data[i] == data[(i+offset) % size]) {
      sum += data[i] - '0';
    }
  }

  return sum;
}


int main(int argc, char** argv) {
  auto results = measure_time(1000, run, argv[1]);
  printf("%u\n", results[0]);
}
