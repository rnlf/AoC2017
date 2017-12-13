#include <utility>
#include <vector>
#include <cstdio>

struct Layer {
  int depth;
  int range;
};


int
scanner_pos(Layer const& l, int time) {
  int pos = time % (l.range - 1);
  int sec = time / (l.range - 1);
  if(sec % 2 == 1) {
    pos = l.range - 1 - pos;
  }
  return pos;
}


std::pair<int, int>
severity(std::vector<Layer> const& layers, int delay) {
  int sev = 0;
  int caught = 0;

  for(auto const& l: layers) {
    int pos = scanner_pos(l, l.depth + delay);

    if(pos == 0) {
      caught++;
      sev += l.depth * l.range;
    }
  }
  
  return {sev, caught};
}


std::vector<Layer>
read_input(char const* input) {
  FILE* f = fopen(input, "r");

  std::vector<Layer> layers;
  for(;;) {
    Layer l;
    int c = fscanf(f, "%d: %d ", &l.depth, &l.range);
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
  auto layers = read_input(argv[1]);

  printf("%d\n", severity(layers, 0).first);

  for(int i = 0;; ++i) {
    auto [s, c] = severity(layers, i);
    
    if(c == 0) {
      printf("%d\n", i);
      break;
    }
  }
}
