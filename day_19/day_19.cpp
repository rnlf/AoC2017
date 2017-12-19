#include <memory>
#include <cstdio>


struct Maze {
  int start_x;
  int width;
  int height;

  std::unique_ptr<char[]> maze;

  Maze(char const *filename) {
    FILE *f = fopen(filename, "r");

    fseek(f, 0, SEEK_END);
    long s = ftell(f);
    fseek(f, 0, SEEK_SET);

    maze = std::make_unique<char[]>(s+1);
    fread(maze.get(), 1, s, f);
    
    maze[s] = 0;

    fclose(f);

    width = 0;
    while(maze[width] != '\n') {
      if(maze[width] == '|') {
        start_x = width;
      }
      ++width;
    }
    ++width;

    height = s / width;
  }

  char get(int x, int y) const {
    if(x < 0 || x >= width || y < 0 || y >= height) {
      return ' ';
    }
    return maze[width * y + x];
  }

};


struct Dir {
  int dx;
  int dy;
};


static constexpr Dir dirs[] = {
  {0,1},
  {1,0},
  {0,-1},
  {-1,0}
};

int main(int argc, char** argv) {
  Maze maze(argv[1]);

  auto dir = 0;

  int x = maze.start_x;
  int y = 0;

  int count = 0;
  for(;;) {
    auto const& d = dirs[dir];
    char cur = maze.get(x, y);
    while(cur != '+' && cur != ' ') {
      ++count;
      if(cur >= 'A' && cur <= 'Z') {
        printf("%c", cur);
      }
      x = x + d.dx;
      y = y + d.dy;
      cur = maze.get(x, y);
    }

    int newdir = dir;
    for(int i = 3; i < 6; ++i) {
      int newdir2 = (dir + i) % 4;
      auto const& td = dirs[newdir2];
      if(maze.get(x + td.dx, y + td.dy) != ' ') {
        newdir=newdir2;
        break;
      }
    }

    if(newdir == dir) {
      break;
    }
    dir = newdir;
    x += dirs[dir].dx;
    y += dirs[dir].dy;
    ++count;
    if(cur >= 'A' && cur <= 'Z') {
      printf("%c", cur);
    }
  }

  printf("\n");
  printf("%d\n", count);

}
