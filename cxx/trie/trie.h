#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <unordered_map>

struct Data{};  // just to show that we can keep some data in tree

struct Node {
  bool marker{false};
  const Data* data{nullptr};

  using Children = std::unordered_map<std::string, Node*>;
  Children children;

  ~Node() noexcept;
};

struct Trie {
  void Insert(const std::string& key, const Data* data = nullptr);
  ~Trie() noexcept;

  Node::Children children;
};

#endif  // TRIE_H
