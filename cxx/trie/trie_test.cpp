#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <string>
#include <string_view>
#include <unordered_map>

using ::testing::Eq;
using ::testing::Contains;
using ::testing::Key;

struct Node {
  using Children = std::unordered_map<std::string, Node*>;
  int data;
  Children children;
  ~Node() noexcept {
    for (auto [_, n]: children)
      delete n;
  }
};

struct Trie {
  Node::Children children;
  ~Trie() noexcept {
    for (auto [_, n]: children)
      delete n;
  }
};

bool ContainsChild(const Node::Children& children, std::string key) {
  return children.find(key) != children.end();
}

int FindBegin(std::string key, std::string new_key) {
  auto min = std::min(key.length(), new_key.length());
  for (auto i = 0; i < min; ++i) {
    if (key[i] != new_key[i]) return i;
  }
  return min;
}

std::pair<Node*, int> FindSimilar(const Node::Children& children, std::string new_key) {
  for (auto [key, node]: children) {
    auto i = FindBegin(key, new_key);
    if (i > 0) {
      return std::make_pair(node, i);
    }
  }
  return std::make_pair(nullptr, 0);
}

void Insert(Trie& tree, std::string_view key, int data) {
  auto child = FindSimilar(tree.children, key);
  if (!child.first) {
    tree.children.emplace(key, new Node{data, {}});
  } else {
    
  }
}

TEST(TestTrie, InsertIntoEmptyTree) {
  Trie tree;
  Insert(tree, "One", 1);

  EXPECT_THAT(tree.children, Contains(Key("One")));
  EXPECT_THAT(tree.children.at("One")->data, Eq(1));
}

TEST(TestTrie, InsertTwoDifferentElements) {
  Trie tree;
  Insert(tree, "One", 1);
  Insert(tree, "Two", 2);

  EXPECT_THAT(tree.children, Contains(Key("One")));
  EXPECT_THAT(tree.children, Contains(Key("Two")));
}

TEST(TestTrie, InsertTwoSimilarElements) {
  Trie tree;
  Insert(tree, "One", 1);
  Insert(tree, "Once", 2);

  EXPECT_THAT(tree.children, Contains(Key("On")));
//  auto root = tree.children.at("On");
//  EXPECT_THAT(root->children, Contains(Key("e")));
//  EXPECT_THAT(root->children.at("e")->data, Eq(1));
//  EXPECT_THAT(root->children, Contains(Key("ce")));
//  EXPECT_THAT(root->children.at("ce")->data, Eq(2));
}
