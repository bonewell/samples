#include "trie.h"

#include <string_view>

namespace {
size_t FindBegin(std::string key, std::string_view new_key) {
  auto min = std::min(key.length(), new_key.length());
  for (auto i = 0; i < min; ++i) {
    if (key[i] != new_key[i]) return i;
  }
  return min;
}

std::pair<Node::Children::const_iterator, size_t>
FindSimilar(const Node::Children& children, std::string_view key) {
  for (auto it = std::begin(children); it != std::end(children); ++it) {
    auto i = FindBegin(it->first, key);
    if (i > 0) {
      return std::make_pair(it, i);
    }
  }
  return std::make_pair(std::end(children), 0u);
}

Node::Children::iterator AddElement(Node::Children& children, const std::string& key, Node* node) {
  try {
    return children.emplace(key, node).first;
  } catch (...) {
    delete node;
    throw;
  }
}

void DeleteElement(Node::Children& children, Node::Children::const_iterator it) {
  children.erase(it);
}
}  // namespace

Node::~Node() noexcept {
  for (auto [_, n]: children)
    delete n;
}

void Node::Insert(const std::string& key, const Data* data) {
  auto [it, pos] = FindSimilar(children, key);
  if (it == std::end(children)) {
    AddElement(children, key, new Node{true, data, {}});
  } else if (it->first == key.substr(0, pos)) {
    it->second->Insert(key.substr(pos), data);
  } else {
    auto old_key = it->first;
    auto old_node = it->second;
    DeleteElement(children, it);
    auto nit = AddElement(children, old_key.substr(0, pos), new Node{false, nullptr, {}});
    AddElement(nit->second->children, key.substr(pos), new Node{true, data, {}});
    AddElement(nit->second->children, old_key.substr(pos), old_node);
  }
}

void Trie::Insert(const std::string& key, const Data* data) {
  Node::Insert(key, data);
}
