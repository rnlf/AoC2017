#include <queue>
#include <string>
#include "../day_10/knot_hash.h"


uint16_t find_start(uint8_t const* grid) {
  for(uint16_t i = 0; i < 128*128; ++i) {
    if(grid[i] != 0) {
      return i;
    }
  }
  return 0xFFFF;
}

void print_pos(uint16_t index) {
  printf("%u, %u\n", index % 128, index / 128);
}

uint16_t index(uint16_t x, uint16_t y) {
  return 128*y + x;
}


void check(std::queue<uint16_t>& next, uint8_t *grid, uint16_t index) {
  if(grid[index] == 1) {
    next.push(index);
    grid[index] = 0;
  }
}


int main(int argc, char ** argv) {
  std::string input {argv[1]};

  unsigned count = 0;
  uint8_t grid[128*128] = {0};
  for(uint16_t i = 0; i < 128; ++i) {
    std::string row_input = input + "-" + std::to_string(i);

    auto hash = knot_hash(row_input);

    // count bits naively
    for(uint16_t j = 0; j < 16; ++j) {
      uint8_t byte = hash.data[j];
      for(int k = 0; k < 8 ; ++k) {
        uint8_t here = !!(byte & 0x80);
        grid[i*128+8*j + k] = here;
        count += here;
        byte <<= 1;
      }
    }
  }

  printf("%d\n", count);

  
  unsigned regions = 0;
  for(;;) {
    std::queue<uint16_t> next;
    uint16_t start = find_start(grid);
    if(start == 0xffff) {
      break;
    }
    grid[start] = 0;
    next.push(start);
    regions++;

    while(!next.empty()) {
      uint16_t index = next.front();
      next.pop();

      if(index >= 128) {
        check(next, grid, index - 128);
      }

      if(index < 128*127) {
        check(next, grid, index + 128);
      }

      if((index & 0x7f) != 0) {
        check(next, grid, index - 1);
      }

      if((index & 0x7f) != 127) {
        check(next, grid, index + 1);
      }
    }
  }

  printf("%u regions\n", regions);
  

}
