#include <cstdint>
#include <cstdio>
#include <queue>


struct Program {
  uint16_t neighbors[10];
  uint8_t count = 0;
  bool visited = false;
};


bool find_group(Program *programs, int prg_count) {
  std::queue<uint16_t> queue;
  int i;
  for(i = 0; i < prg_count; ++i) {
    if(!programs[i].visited) {
      queue.push(i);
      break;
    }
  }
  if(i == prg_count) {
    return false;
  }

  int count = 0;
  while(!queue.empty()) {
    uint16_t next = queue.front();
    queue.pop();
    auto &prg = programs[next];
    if(!prg.visited) {
      count++;
      prg.visited = true;
      for(int i = 0; i < prg.count; ++i) {
        queue.push(prg.neighbors[i]);
      }
    }
  }

  #ifndef PART2
  printf("%d\n", count);
  #endif

  return true;
}


int main(int argc, char** argv) {
  FILE* f = fopen(argv[1], "r");

  Program programs[4000];
  int prg_count = 0;


  for(;;) { 
    unsigned prg_idx;
    int c = fscanf(f, "%u <-> ", &prg_idx);
    if(c != 1) {
      break;
    }
    prg_count++;
    auto &prog = programs[prg_idx];

    for(;;) {
      fscanf(f, " %hu", &prog.neighbors[prog.count]);
      prog.count++;
      int c = fgetc(f);
      if(c != ',') {
        break;
      }
    }
  }

  fclose(f);

  #ifdef PART2
  int total = 0;
  while(find_group(programs, prg_count)) {
    total++;
  }

  printf("%u\n", total);
  #else
  find_group(programs, prg_count);
  #endif

}

