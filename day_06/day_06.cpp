#include <cstring>
#include <unordered_map>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <cstdint>
#include <vector>
#include "../fileread.h"
#include "../timer.h"


static uint8_t constexpr bank_count = 16;
static uint8_t constexpr bank_mask  = bank_count - 1;

struct Memory {
  uint8_t banks[bank_count];
};

bool operator==(Memory const& a, Memory const& b) {
  return memcmp(&a, &b, sizeof(Memory)) == 0;
}


struct MemoryHash {
  size_t operator()(Memory const& mem) const {
    uint64_t const * p = reinterpret_cast<uint64_t const*>(&mem.banks);
    return p[0] ^ p[1];
  }
};


Memory
redistribute(Memory mem) {
  uint8_t * const max         = std::max_element(mem.banks, &mem.banks[bank_count]);
  uint8_t const   max_i       = max - &mem.banks[0];
  uint8_t const   max_v       = *max;

  *max = 0;
  for(uint8_t i = 0; i < max_v; ++i) {
    ++mem.banks[(max_i+i+1) & bank_mask];
  }

  return mem;
}


int
run(char const* filename) {
  auto const banks = read_numbers<uint8_t>(filename, 16);
  
  std::unordered_map<Memory, unsigned, MemoryHash> seen_configurations;
  Memory start;
  memcpy(start.banks, banks.data(), sizeof(start.banks));
  seen_configurations.insert({start, 0});

  for(unsigned step = 1; ++step;) {
    start = redistribute(start);
    auto ins = seen_configurations.insert({start, step});
    if(!ins.second) {
      #ifdef PART2
        return step - ins.first->second;
      #else
        return seen_configurations.size();
      #endif
    }
  }
}


int
main(int argc, char** argv) {
  auto results = measure_time(100, &run, argv[1]);
  printf("%d\n", results[1]);
}
