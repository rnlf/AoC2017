#include <numeric>
#include <utility>
#include <vector>
#include <cstdio>

struct Layer {
  int depth;
  int range;
};


int
scanner_pos(Layer const& l, int const time) {
  int const pos = time % (l.range - 1);
  int const sec = time / (l.range - 1);
  if(sec % 2 == 1) {
    return l.range - 1 - pos;
  }
  return pos;
}


template<typename S, typename T>
std::pair<S, T>
operator+(std::pair<S, T> const& s, std::pair<S,T> const& t) {
  return {s.first + t.first, s.second + t.second};
}


std::pair<int, int>
severity(std::vector<Layer> const& layers, int const delay) {
  return std::accumulate(layers.begin(), layers.end(), std::pair<int,int> {0, 0},
    [delay](auto const& p, auto const& l) {
      int const mul = !scanner_pos(l, l.depth + delay);
      return p + std::pair<int,int> {mul * l.depth * l.range, mul};
    }
  );
}


std::vector<Layer>
read_input(char const* const input) {
  FILE* f = fopen(input, "r");

  std::vector<Layer> layers;
  for(;;) {
    Layer l;
    int const c = fscanf(f, "%d: %d ", &l.depth, &l.range);
    if(c != 2) {
      break;
    }
    layers.push_back(l);
  }

  fclose(f);

  return layers;
}


int
main(int argc, char** argv) {
  auto const layers = read_input(argv[1]);

  printf("%d\n", severity(layers, 0).first);

  for(int i = 0;; ++i) {
    int const c = severity(layers, i).second;
    
    if(c == 0) {
      printf("%d\n", i);
      break;
    }
  }
}
