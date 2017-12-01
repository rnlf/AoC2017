#include <cctype>
#include <vector>
#include <cstdio>
#include <string>


int main(int argc, char** argv) {
  FILE* f = fopen(argv[1], "r");
  std::vector<unsigned> data;

  for(;;) {
    int c = fgetc(f);
    if(c == EOF || !isdigit(c)) {
      break;
    }
    data.push_back(c - '0');
  }

  fclose(f);

  unsigned offset = 1;
  if(argc > 2 && std::string(argv[2]) == "--part2") {
    offset = data.size() / 2;
  }
  
  unsigned sum = 0;
  for(int i = 0; i < data.size(); ++i) {
    if(data[i] == data[(i+offset) % data.size()]) {
      sum += data[i];
    }
  }

  printf("%u\n", sum);
}
