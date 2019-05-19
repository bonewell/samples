#include "trie.h"

#include <algorithm>
#include <iterator>
#include <string_view>
#include <utility>

namespace {
/**
 * Compares two strings and return position where is different found
 * @param lhs the first string
 * @param rhs the second string
 * @return position where chars are not equal
 * if strings are absolutely different, position is 0
 * if strings are similar and one of them is just longer,
 * position is std::min(lhs.length(), rhs.length())
 *
 */
size_t Compare(std::string_view lhs, std::string_view rhs) {
  auto min = std::min(lhs.length(), rhs.length());
  for (auto i = 0; i < min; ++i) {
    if (lhs[i] != rhs[i]) return i;
  }
  return min;
}

std::pair<Node::Children::const_iterator, size_t>
FindSimilarKey(const Node::Children& children, std::string_view key) {
  for (auto it = std::cbegin(children); it != std::cend(children); ++it) {
    auto pos = Compare(it->first, key);
    if (pos > 0) {
      return {it, pos};
    }
  }
  return {std::cend(children), 0u};
}

const Node* FindElement(const Node::Children& children, std::string_view key) {
  const auto& [it, pos] = FindSimilarKey(children, key);
  if (pos > 0) {
    if (it->first == key) {  // the same
      return it->second;
    } else if (it->first == key.substr(0, pos)) {  // it->first is begin of key
      return FindElement(it->second->children, key.substr(pos));
    }
  }
  return nullptr;
}

std::ostream& PrintChildren(std::ostream& out , const Node::Children& children, int deep) {
  std::string prefix(deep, '-');
  for (const auto& p: children) {
    out << prefix << p.first << "\n";
    PrintChildren(out, p.second->children, deep + 1);
  }
  return out;
}
}  // namespace

Node::~Node() noexcept {
  std::for_each(std::cbegin(children), std::cend(children),
                [](const auto& c) { delete c.second; });
}

Node* Node::AddChild(const std::string& key, bool marker, const Data* data,
    Node::Children&& children) {
  auto node = new Node{marker, data, children};
  try {
    this->children.emplace(key, node);
  } catch (...) {
    delete node;
    throw;
  }
  return node;
}

void Node::MoveChild(const std::string& key, Node* node) {
  children.emplace(key, node);
}

void Node::MarkChild(const std::string& key, const Data* data) {
  auto node = children[key];
  node->marker = true;
  node->data = data;
}

void Node::UnmarkChild(const std::string& key) {
  auto node = children[key];
  node->marker = false;
  node->data = nullptr;
}

void Node::DeleteChild(const std::string& key) {
  children.erase(key);
}

void Node::DeleteElement(Node::Children::const_iterator it) {
  if (it->second->marker) {
    auto key = it->first;
    auto node = it->second;
    if (node->children.empty()) {
      delete node;
      DeleteChild(key);
    } else if (node->children.size() == 1) {
      auto child_key = node->children.begin()->first;
      auto child_node = node->children.begin()->second;
      MoveChild(key + child_key, child_node);
      DeleteChild(key);
    } else {
      UnmarkChild(key);
    }
  }
}

void Node::Insert(std::string key, const Data* data) {
  const auto& [it, pos] = FindSimilarKey(children, key);
  if (pos == 0) {
    AddChild(key, true, data);
  } else if (it->first == key) {
    MarkChild(it->first, data);
  } else if (it->first == key.substr(0, pos)) {
    it->second->Insert(key.substr(pos), data);
  } else if (it->first.substr(0, pos) == key) {
    auto node = AddChild(key, true, data);
    node->MoveChild(it->first.substr(pos), it->second);
    DeleteChild(it->first);
  } else {
    auto node = AddChild(it->first.substr(0, pos), false, nullptr);
    node->AddChild(key.substr(pos), true, data);
    node->MoveChild(it->first.substr(pos), it->second);
    DeleteChild(it->first);
  }
}

Node::Result Node::Find(std::string_view key) const {
  auto node = FindElement(children, key);
  if (node) {
    return {node->marker, node->data};
  }
  return {false, nullptr};
}

void Node::Compress(Node* parent, const std::string& key) {
  for (auto it = std::begin(children); it != std::end(children); ++it) {
    it->second->Compress(this, it->first);
  }
  if (parent && !parent->marker && children.size() == 1) {
    auto child_key = children.begin()->first;
    auto child_node = children.begin()->second;
    parent->MoveChild(key + child_key, child_node);
    DeleteChild(child_key);
  }
}

void Node::RemoveElement(std::string_view key) {
  const auto& [it, pos] = FindSimilarKey(children, key);
  if (it->first == key) {
    DeleteElement(it);
  } else if (it->first == key.substr(0, pos)) {
    it->second->Remove(key.substr(pos));
  }
}

void Node::Remove(std::string_view key) {
  RemoveElement(key);
  Compress(nullptr, "");
}

std::ostream& operator<<(std::ostream& out, const Trie& tree) {
  return PrintChildren(out, tree.children, 0);
}
