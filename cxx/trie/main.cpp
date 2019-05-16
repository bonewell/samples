#include "trie.h"

#include <algorithm>
#include <iostream>

int main(int argc, char* argv[]) {
  if (argc == 2) {
      std::cerr << "Use: " << argv[0] << " <word_to_search> <word> [<word_2>... <word_n>]\n";
      return -1;
  }

  std::string key = argv[1];

  Trie tree;
  for (auto i = 2; i < argc; ++i) {
    tree.Insert(argv[i]);
  };

  std::cout << tree << "\n";

  auto [res, _] = tree.Find(key);
  std::cout << "Tree contains `" << key << "` word: " << std::boolalpha << res << "\n";
}
