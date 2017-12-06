#include <cstdio>
#include <vector>

template<typename T>
std::vector<T>
read_numbers(char const* filename, size_t reserve=1024) {
  bool constexpr is_unsigned = std::is_unsigned_v<T>;
  typedef std::conditional_t<is_unsigned, unsigned, int> read_type;

  std::vector<T> nums;
  nums.reserve(reserve);

  FILE* f = fopen(filename, "r");
  
  read_type tmp;
  while(fscanf(f, is_unsigned ? " %u" : " %d", &tmp) > 0) {
    nums.push_back(T(tmp));
  }

  fclose(f);

  return nums;
}

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
