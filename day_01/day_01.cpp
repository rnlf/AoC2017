#include <vector>
#include <string>
#include "../timer.h"
#include "../fileread.h"


int main(int argc, char** argv) {
  Timer timer;

  auto const file = read_file(argv[1]);

  std::vector<unsigned> data;
  data.reserve(file.size());

  for(int i = 0; file[i] != '\n'; ++i) {
    data.push_back(file[i] - '0');
  }

  #ifdef PART2
    static unsigned const offset = data.size() / 2;
  #else
    static unsigned constexpr offset = 1;
  #endif
  
  unsigned sum = 0;
  for(int i = 0; i < data.size(); ++i) {
    if(data[i] == data[(i+offset) % data.size()]) {
      sum += data[i];
    }
  }

  printf("%u\n", sum);
}
