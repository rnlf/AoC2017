#include <algorithm>
#include <cstring>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <vector>
#include "../timer.h"


int run(char const* filename) {

  FILE *f = fopen(filename, "r");
  
  uint64_t cur_word = 0;
  int count = 0;
  std::vector<uint64_t> words_in_line;
  words_in_line.reserve(50);
  for(;;) {
    int cur_char = fgetc(f);

    if(cur_char == EOF) {
      break;

    } else if(cur_char >= 'a' && cur_char <= 'z') {
      cur_word <<= 8;
      cur_word |= cur_char;

    } else {
      
      count += [&] {
        if(cur_word > 0) {
          #ifdef PART2
          uint8_t *wp = reinterpret_cast<uint8_t*>(&cur_word);
          std::sort(wp, wp+sizeof(uint64_t));
          #endif

          if(std::find(words_in_line.begin(), words_in_line.end(), cur_word) != words_in_line.end()) {
            while(cur_char != '\n') {
              cur_char = fgetc(f);
            }
            words_in_line.clear();
            return 0;
          }

          words_in_line.push_back(cur_word);
        }

        if(cur_char == '\n') {
          words_in_line.clear();
          return 1;
        }
        return 0;
      }();

      cur_word = 0;
    }
  }
  fclose(f);

  return count;
}

int main(int argc, char** argv) {
  auto const results = measure_time(1000, run, argv[1]);
  printf("%u\n", results[0]);
}
