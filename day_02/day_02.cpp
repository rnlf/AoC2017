#include <vector>
#include <algorithm>
#include <cctype>
#include <limits>
#include <cstdio>
#include "../timer.h"

#ifdef PART2
unsigned filter(std::vector<unsigned> const& numbers) {
  for(unsigned i = 0; i < numbers.size()-1; ++i) {
    unsigned const a = numbers[i];
    for(unsigned j = i+1; j< numbers.size(); ++j) {
      unsigned const b = numbers[j];
      unsigned low = std::min(a, b);
      unsigned high = std::max(a, b);
      if(high % low == 0) {
        return high / low;
      }
    }
  }
  return 0;
}
#endif


unsigned run(char const* const filename) {
  FILE* f = fopen(filename, "r");

  unsigned sum = 0;

#ifdef PART2
  std::vector<unsigned> numbers;
  numbers.reserve(100);
#else
  unsigned row_low  = std::numeric_limits<unsigned>::max();
  unsigned row_high = std::numeric_limits<unsigned>::min();
#endif

  unsigned cur_num = 0;
  for(;;) {
    int const cur_char = fgetc(f);
    if(cur_char == EOF) {
      break; 
    } else if(std::isdigit(cur_char)) {
      cur_num = cur_num * 10 + cur_char - '0';
    } else {
#ifdef PART2
      numbers.push_back(cur_num);
#else
      row_low  = std::min(row_low,  cur_num);
      row_high = std::max(row_high, cur_num);
#endif
      cur_num = 0;

      if(cur_char == '\n') {
#ifdef PART2
        sum += filter(numbers);
        numbers.clear();
#else
        sum += row_high - row_low;
        row_low  = std::numeric_limits<unsigned>::max();
        row_high = std::numeric_limits<unsigned>::min();
#endif
      }
    }
  }
  fclose(f);

  return sum;
}


int main(int argc, char** argv) {
  auto const results = measure_time(1000, run, argv[1]);
  printf("%u\n", results[0]);
}
