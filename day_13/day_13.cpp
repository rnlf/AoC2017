#include <algorithm>
#include <numeric>
#include <vector>
#include <cstdio>
#include "../timer.h"

struct Layer {
  int16_t depth;
  int16_t range;
};


bool
scanner_zero(Layer const& l, int const time) {
  return !(time % (2 * (l.range - 1)));
}


bool
detected(std::vector<Layer> const& layers, int const delay) {
  for(auto const& l: layers) {
    if(scanner_zero(l, l.depth + delay)) {
      return true;
    }
  }

  return false;
}


int
severity(std::vector<Layer> const& layers, int const delay) {
  return std::accumulate(layers.begin(), layers.end(), 0,
    [delay](auto const& p, auto const& l) {
      return p + (scanner_zero(l, l.depth + delay) ? (l.depth * l.range) : 0);
    }
  );
}


std::vector<Layer>
read_input(char const* const input) {
  FILE* f = fopen(input, "r");

  std::vector<Layer> layers;
  for(;;) {
    Layer l;
    int const c = fscanf(f, "%hd: %hd ", &l.depth, &l.range);
    if(c != 2) {
      break;
    }
    layers.push_back(l);
  }

  fclose(f);

  return layers;
}


int
part2(std::vector<Layer> const& layers) {
  std::vector<Layer> l2(layers);

  // This reduces the time needed for the search by 26%!
  std::sort(l2.begin(), l2.end(), [](auto const& a, auto const& b) { return a.range < b.range; });

  for(int i = 0;; ++i) {
    if(!detected(l2, i)) {
      return i;
    }
  }
}


int
main(int argc, char** argv) {
  auto const layers = read_input(argv[1]);

  printf("%d\n", severity(layers, 0));

  auto const res = measure_time(100, &part2, layers);
  printf("%d\n", res[0]);

}
