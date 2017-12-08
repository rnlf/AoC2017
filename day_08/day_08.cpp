#include <algorithm>
#include <unordered_map>
#include <cstdint>
#include <cstdio>


struct Instruction {
  uint32_t reg;
  uint32_t inc;
  int amount;
  uint32_t cond_reg;
  uint32_t comp;
  int ref;
};


uint16_t constexpr make_cond(uint8_t a, uint8_t b) {
  return a << 8 | b;
}


int main(int argc, char** argv) {
  FILE* f = fopen(argv[1], "r");

  std::unordered_map<uint32_t, int> regs;

  int max=0;

  for(;;) {
    uint32_t reg = 0;
    int amount;
    uint32_t cond_reg = 0;
    char comp[3];
    int ref;


    char incdec[4];
    int r = fscanf(f, "%s %s %d if %s %s %d ",
      reinterpret_cast<char*>(&reg),
      incdec,
      &amount,
      reinterpret_cast<char*>(&cond_reg),
      comp,
      &ref);

    if(r != 6) {
      break;
    }

    int ref_reg = regs[cond_reg];
    uint16_t c = make_cond(comp[0], comp[1]);

    bool res = [=]() {
      switch(c) {
      case make_cond('!', '='):
        return (ref_reg != ref);

      case make_cond('=', '='):
        return (ref_reg == ref);

      case make_cond('<', '='):
        return (ref_reg <= ref);

      case make_cond('>', '='):
        return (ref_reg >= ref);

      case make_cond('>', 0):
        return (ref_reg > ref);

      case make_cond('<', 0):
        return (ref_reg < ref);
      }
    }();

    if(res) {
      auto &rv = regs[reg];
      rv += incdec[0] == 'i' ? amount : -amount;
      max = std::max(rv, max);
    }
  }
  fclose(f);

  auto m = std::max_element(regs.begin(), regs.end(), [](auto a, auto b) { return a.second < b.second; });

  printf("%s = %d\n", reinterpret_cast<char const*>(&m->first), m->second);
  printf("%d\n", max);
}
