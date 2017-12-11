#include <utility>
#include <cstdio>


int skip_garbage(FILE *f) {
  int garbage=0;
  for(;;) {
    int c = fgetc(f);

    if(c == '!') {
      fgetc(f);
    } else if(c == '>') {
      return garbage;
    } else {
      garbage++;
    }
  }
}


std::pair<int,int> parse_group(FILE* f, int score);


std::pair<int,int> parse_group_list(FILE* f, int score) {
  int sum = score;
  int garb = 0;
  for(;;) {
    int c = fgetc(f);

    if(c == EOF) {
      break;
    }

    switch(c) {
    case '<':
      garb += skip_garbage(f);
      break;

    case '{':
      {
        auto [s, g] = parse_group(f, score+1);
        sum += s;
        garb += g;
      }
      break;

    case '}':
      return {sum, garb};

    case ',':
      break;

    case '\n':
      if(score == 0) {
        return {sum, garb};
      }

    default:
      printf("Unexpected: '%c'\n", c);
      break;
      
    }
  }

  return {sum, garb};
  
}


std::pair<int,int> parse_group(FILE* f, int score) {
  return parse_group_list(f, score);
}


int main(int argc, char** argv) {
  FILE *f = fopen(argv[1], "r");

  auto [s, g] = parse_group(f, 0);
  printf("%d\n", s);
  printf("%d\n", g);
  
  fclose(f);

}
