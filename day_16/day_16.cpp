#include <string>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <cstdint>


struct Move {
  char type;
  int a;
  int b;
  char x;
  char y;
};


int main(int argc, char **argv) {
  char programs[2][17];
  for(int i = 0; i < 16; ++i) {
    programs[0][i] =  i + 'a';
    programs[1][i] =  i + 'a';
  }
  programs[0][16] = 0;
  programs[1][16] = 0;

  std::vector<Move> moves;
  FILE *f = fopen(argv[1], "r");

  for(;;) {
    int c = fgetc(f);
    Move move;
    move.type = c;
    switch(c) {
    case 'x':
      {
        fscanf(f, "%d/%d", &move.a, &move.b);
      }
      break;

    case 's':
      {
        fscanf(f, "%d", &move.a);
      }
      break;

    case 'p':
      {
        fscanf(f, "%c/%c", &move.x, &move.y);
      }
      break;
    }
    moves.push_back(move);
    c = fgetc(f);
    if(c != ',') {
      break;
    }
  }

  fclose(f);


  #if PART2
  std::vector<std::string> patterns;
  bool cycle = false;
  for(int j = 0; j < 1000000000; ++j) {
  #endif
    for(auto const& move: moves) {
      switch(move.type) {
      case 'x':
        {
          char tmp = programs[0][move.a];
          programs[0][move.a] = programs[0][move.b];
          programs[0][move.b] = tmp;
        }
        break;

      case 's':
        {
          std::rotate(programs[0], programs[0] + 16 - move.a, programs[0] + 16);
        }
        break;

      case 'p':
        {
          int x = std::find(programs[0], programs[0]+16, move.x) - programs[0];
          int y = std::find(programs[0], programs[0]+16, move.y) - programs[0];
          char tmp = programs[0][x];
          programs[0][x] = programs[0][y];
          programs[0][y] = tmp;
        }
        break;
      }
    }
    
    #ifdef PART2
    if(!cycle) {
      std::string new_pattern {programs[0]};
      auto it= std::find(patterns.begin(), patterns.end(), new_pattern);
      if(it != patterns.end()) {
        auto cycle_length = patterns.end() - it;
        // This could be done much quicker by just looking up the correct entry in the cycle, but
        // I don't feel like proceeding here anymore, it's good enough
        j += (((1000000000 - j) / cycle_length) * cycle_length);
        cycle = true;
      } else {
        patterns.push_back(new_pattern);
      }
    }
  }
  #endif

  printf("%s\n", programs[0]);
}

