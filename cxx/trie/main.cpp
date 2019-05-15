#include "trie.h"

#include <algorithm>
#include <iostream>

int main(int argc, char* argv[]) {
  if (argc == 1) {
      std::cerr << "Use: " << argv[0] << " <word> [<word_2>... <word_n>]\n";
      return -1;
  }

  Trie tree;
  for (auto i = 1; i < argc; ++i) {
    tree.Insert(argv[i]);
  };

  std::cout << tree << "\n";
}
