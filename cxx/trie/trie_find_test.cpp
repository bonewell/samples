#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "trie.h"

using ::testing::Eq;

TEST(TrieFindTest, FindElementOnFirstLevel) {
  Trie tree;
  tree.children.emplace("One", new Node{true, nullptr, {}});

  EXPECT_THAT(tree.Find("One").first, Eq(true));
}

TEST(TrieFindTest, NoElementOnFirstLevel) {
  Trie tree;
  tree.children.emplace("On", new Node{});
  tree.children.at("On")->children.emplace("e", new Node{true, nullptr, {}});
  tree.children.at("On")->children.emplace("ce", new Node{true, nullptr, {}});

  EXPECT_THAT(tree.Find("On").first, Eq(false));
}

TEST(TrieFindTest, FindElementOnSecondLevel) {
  Trie tree;
  tree.children.emplace("On", new Node{});
  tree.children.at("On")->children.emplace("e", new Node{true, nullptr, {}});
  tree.children.at("On")->children.emplace("ce", new Node{true, nullptr, {}});

  EXPECT_THAT(tree.Find("Once").first, Eq(true));
}

TEST(TrieFindTest, NoElementWithShortKey) {
  Trie tree;
  tree.children.emplace("Deepwater", new Node{true, nullptr, {}});

  EXPECT_THAT(tree.Find("Deep").first, Eq(false));
}

TEST(TrieFindTest, NoElementWithLongKey) {
  Trie tree;
  tree.children.emplace("Deep", new Node{true, nullptr, {}});

  EXPECT_THAT(tree.Find("Deepwater").first, Eq(false));
}
