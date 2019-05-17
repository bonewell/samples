#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <string>
#include <unordered_map>

struct Data{};  // just to show that we can keep some data in tree

struct Node {
  bool marker{false};
  const Data* data{nullptr};

  using Children = std::unordered_map<std::string, Node*>;
  Children children;

  void Insert(std::string_view key, const Data* data = nullptr);
  void Remove(const std::string& key);

  using Result = std::pair<bool, const Data*>;
  Result Find(std::string_view key) const;
  ~Node() noexcept;
};

using Trie = Node;

std::ostream& operator<<(std::ostream& out, const Trie& tree);

#endif  // TRIE_H
