#include <vector>
#include <cstdio>
#include "../timer.h"
#include "../fileread.h"


std::vector<int>
read_jumps(char const* filename) {
  return read_numbers<int>(filename);
}


int
run(char const* filename) {
  auto jumps = read_jumps(filename);

  int pc = 0;
  int count = 0;
  while(pc >= 0 && pc < jumps.size()) {
    int &j         = jumps[pc];
    int const jump = j;

    static int constexpr displace[] = {1, -1};

    #ifdef PART2
      j += displace[jump >= 3];
    #else
      ++j;
    #endif

    pc = pc + jump;
    ++count;
  }

  return count;
}


int
main(int argc, char** argv) {
  auto results = measure_time(100, &run, argv[1]);
  printf("%d\n", results[1]);
}
