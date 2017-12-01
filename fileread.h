#include <cstdio>
#include <vector>


std::vector<char>
read_file(char const* const filename) {
  FILE * const f = fopen(filename, "r");
  fseek(f, 0, SEEK_END);
  auto const len = ftell(f);
  fseek(f, 0, SEEK_SET);

  auto dat = std::vector<char>(len);
  fread(dat.data(), len, 1, f);
  fclose(f);

  return dat;
}
