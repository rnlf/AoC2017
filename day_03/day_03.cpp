#include <cstring>
#include <string>
#include <cmath>
#include <cstdio>

#ifdef PART2
static constexpr size_t mem_size = 1000;

int
index(int x, int y) {
  auto idx = (y+mem_size/2)*mem_size + x + mem_size / 2;
  return idx;
}
#endif


int
main(int argc, char** argv) {
  int const num            = std::stoi(argv[1]);
#ifndef PART2
  int const ring           = int(ceil(sqrt(float(num))))/2;
  int const ring_width     = (2*ring+1);
  int const last_in_ring   = ring_width * ring_width;
  int const from_end       = last_in_ring - num;
  int const offset         = from_end % (ring_width - 1);
  int const ring_distance  = abs(offset - (ring_width / 2));
  int const total_distance = ring + ring_distance;
  printf("%u\n", total_distance);
#else
  // Who cares, just use the hackiest way possible :D


  uint64_t numbers[mem_size * mem_size];
  memset(numbers, 0, sizeof(numbers));

  static const int dirs[4][2] = {
    {1,0}, {0,-1}, {-1, 0}, {0, 1}
  };

  numbers[index(0, 0)] = 1;
  int ring = 0;
  int ring_width = 1;
  int last_in_ring = ring_width * ring_width;
  int x = 0;
  int y = 0;
  int dir = 0;
  for(int i = 0;i < 1000;++i) {
    x += dirs[dir][0];
    y += dirs[dir][1];
    if(dir == 0 && x == ring_width / 2+1) {
      ++ring;
      ring_width += 2;
      dir = 1;
    } else if(dir == 1 && y == -ring_width/2) {
      dir = 2;
    } else if(dir == 2 && x == -ring_width/2) {
      dir = 3;
    } else if(dir == 3 && y == ring_width/2) {
      dir = 0;
    }

    uint64_t sum = 0;
    for(int yo = -1; yo <= 1; ++yo) {
      for(int xo = -1; xo <= 1; ++xo) {
        sum += numbers[index(x+xo, y+yo)];
      }
    }
    if(sum > num) {
      printf("%u\n", sum);
      break;
    }
    numbers[index(x, y)] = sum;
  }
#endif
}
