#include <vector>
#include <cstdio>
#include "../timer.h"


std::vector<int>
read_jumps(char const* filename) {
  std::vector<int> jumps;
  jumps.reserve(1024);

  FILE* f = fopen(filename, "r");
  
  int tmp;
  while(fscanf(f, " %d", &tmp) > 0) {
    jumps.push_back(tmp);
  }

  fclose(f);

  return jumps;
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
