#include <cstdint>
#include <cstdio>


struct Generator {
  uint32_t prev;
  uint32_t fac;
  uint32_t mul;

  uint32_t next() {
    #ifdef PART2
    do {
    #endif
      prev = (prev * uint64_t(fac)) % 2147483647;
    #ifdef PART2
    } while(prev % mul != 0);
    #endif
    return prev;
  }
};


int main(int argc, char ** argv) {
  Generator gen_a {618, 16807, 4};
  Generator gen_b {814, 48271, 8};

  int matches = 0;
  int tests =
  #ifndef PART2
    40000000
  #else
    5000000
  #endif
  ;
  for(int i = 0; i < tests; ++i) {
    matches += ((gen_a.next() & 0xFFFF) == (gen_b.next() & 0xFFFF));
  }

  printf("%d\n", matches);
}
