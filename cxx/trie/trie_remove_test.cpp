#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "trie.h"

using ::testing::Contains;
using ::testing::Eq;
using ::testing::Key;
using ::testing::Not;

TEST(TrieRemoveTest, RemoveElementFromSignleElementTree) {
  Trie tree;
  tree.children["One"] = new Node{true, nullptr, {}};

  tree.Remove("One");

  EXPECT_THAT(tree.children.empty(), Eq(true));
}

TEST(TrieRemoveTest, RemoveElementWithoutChildrenFromFirstLevel) {
  Trie tree;
  tree.children["One"] = new Node{true, nullptr, {}};
  tree.children["Two"] = new Node{true, nullptr, {}};

  tree.Remove("One");

  EXPECT_THAT(tree.children, Not(Contains(Key("One"))));
}

TEST(TrieRemoveTest, NoElementToRemoveFomFirstLevel) {
  Trie tree;
  tree.children["On"] = new Node{};
  tree.children["On"]->children["e"] = new Node{true, nullptr, {}};
  tree.children["On"]->children["ce"] = new Node{true, nullptr, {}};

  tree.Remove("On");

  EXPECT_THAT(tree.children, Contains(Key("On")));
}

TEST(TrieRemoveTest, UnmarkRootElementWithChildren) {
  Trie tree;
  tree.children["Deep"] = new Node{true, nullptr, {}};
  tree.children["Deep"]->children["water"] = new Node{true, nullptr, {}};
  tree.children["Deep"]->children["sea"] = new Node{true, nullptr, {}};

  tree.Remove("Deep");

  ASSERT_THAT(tree.children, Contains(Key("Deep")));
  EXPECT_THAT(tree.children["Deep"]->marker, Eq(false));
}

TEST(TrieRemoveTest, MoveUpChildElementIfGrandParentIsMarked) {
  Trie tree;
  tree.children["Deep"] = new Node{true, nullptr, {}};
  tree.children["Deep"]->children["er"] = new Node{true, nullptr, {}};
  tree.children["Deep"]->children["er"]->children["sea"] = new Node{true, nullptr, {}};

  tree.Remove("Deeper");

  ASSERT_THAT(tree.children["Deep"]->children, Not(Contains(Key("er"))));
  EXPECT_THAT(tree.children["Deep"]->children, Contains(Key("ersea")));
}

TEST(TrieRemoveTest, RemoveParentAndCompressWithSingleChild) {
  Trie tree;
  tree.children["Deep"] = new Node{true, nullptr, {}};
  tree.children["Deep"]->children["sea"] = new Node{true, nullptr, {}};

  tree.Remove("Deep");

  EXPECT_THAT(tree.children, Contains(Key("Deepsea")));
  EXPECT_THAT(tree.children, Not(Contains(Key("Deep"))));
}

TEST(TrieRemoveTest, RemoveElementFromSecondLevel) {
  Trie tree;
  tree.children["On"] = new Node{};
  tree.children["On"]->children["e"] = new Node{true, nullptr, {}};
  tree.children["On"]->children["ce"] = new Node{true, nullptr, {}};
  tree.children["On"]->children["ion"] = new Node{true, nullptr, {}};

  tree.Remove("Once");

  EXPECT_THAT(tree.children["On"]->children, Not(Contains(Key("ce"))));
}

TEST(TrieRemoveTest, RemoveChildAndCompressWithParentLastChild) {
  Trie tree;
  tree.children["On"] = new Node{};
  tree.children["On"]->children["e"] = new Node{true, nullptr, {}};
  tree.children["On"]->children["ce"] = new Node{true, nullptr, {}};

  tree.Remove("One");

  EXPECT_THAT(tree.children, Contains(Key("Once")));
}
