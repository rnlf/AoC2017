#include <optional>
#include <cstdio>
#include <vector>
#include <string>
#include <map>


struct Node {
  uint64_t name;
  uint64_t parent = 0;
  uint64_t children[10] = {0};
  int weight;
  int combined_weight;
};


std::optional<Node>
read_node(FILE* f) {
  Node node;

  if(fscanf(f, "%[a-z] (%u) ", reinterpret_cast<char*>(&node.name), &node.weight) != 2) {
    return {};
  }

  int c = fgetc(f);

  if(c != '-') {
    if(c != EOF) {
      ungetc(c, f);
    }
    return node;
  }

  fscanf(f, "> ");

  for(int child_idx = 0; child_idx < 10; ++child_idx) {
    fscanf(f, "%[a-z]", reinterpret_cast<char*>(node.children + child_idx));

    int c = fgetc(f);
    if(c != ',') {
      if(c != EOF) {
        fscanf(f, " ");
      }
      return node;
    }

    fscanf(f, " ");
  }

  return node;
}


auto read_nodes(FILE *f) {
  std::map<uint64_t, Node> nodes;

  for(;;) {
    auto new_node = read_node(f);
    if(!new_node) {
      break;
    }
    nodes[new_node->name] = *new_node;
  }

  for(auto& parent: nodes) {
    for(int i = 0; parent.second.children[i] != 0; ++i) {
      nodes[parent.second.children[i]].parent = parent.second.name;
    }
  }

  return nodes;
}


auto read_input(char const * filename) {
  FILE* f = fopen(filename, "r");
  auto nodes = read_nodes(f);
  fclose(f);

  return nodes;
}


int compute_combined_weight(std::map<uint64_t, Node> & nodes, uint64_t cur) {
  Node &n = nodes[cur];
  int weight = n.weight;

  bool unbalanced = false;
  for(int i = 0; n.children[i] != 0; ++i) {
    int subweight = compute_combined_weight(nodes, n.children[i]);
    nodes[n.children[i]].combined_weight = subweight;
    weight += subweight;

    if(i > 0) {
      if(subweight != nodes[n.children[0]].combined_weight) {
        unbalanced = true;
      }
    }
  }

  if(unbalanced) {
    for(int i = 0; n.children[i] != 0; ++i) {
      printf("%d, %d\n", nodes[n.children[i]].combined_weight, nodes[n.children[i]].weight);
    }
    printf("\n\n\n");
  }

  return weight;
}



int main(int argc, char** argv) {
  auto tree = read_input(argv[1]);

  uint64_t root;
  for(auto const& n: tree) {
    if(n.second.parent == 0) {
      root = n.first;
      break;
    }
  }

  printf("%s\n", reinterpret_cast<char const*>(&root));

  tree[root].combined_weight = compute_combined_weight(tree, root);
}
