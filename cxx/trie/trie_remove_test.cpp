#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "trie.h"

using ::testing::Contains;
using ::testing::Eq;
using ::testing::Key;
using ::testing::Not;

TEST(TrieRemoveTest, DISABLED_RemoveElementFromFirstLevel) {
  Trie tree;
  tree.children.emplace("One", new Node{true, nullptr, {}});

  tree.Remove("One");
  EXPECT_THAT(tree.children.empty(), Eq(true));
}

TEST(TrieRemoveTest, DISABLED_NoElementToRemoveOnFirstLevel) {
  Trie tree;
  tree.children.emplace("On", new Node{});
  tree.children.at("On")->children.emplace("e", new Node{true, nullptr, {}});
  tree.children.at("On")->children.emplace("ce", new Node{true, nullptr, {}});

  tree.Remove("On");
  EXPECT_THAT(tree.children, Contains(Key("On")));
}

TEST(TrieRemoveTest, DISABLED_UnmarkElementWithChildren) {
  Trie tree;
  tree.children.emplace("Deep", new Node{true, nullptr, {}});
  tree.children.at("Deep")->children.emplace("water", new Node{true, nullptr, {}});
  tree.children.at("Deep")->children.emplace("sea", new Node{true, nullptr, {}});

  tree.Remove("Deep");
  ASSERT_THAT(tree.children, Contains(Key("Deep")));
  EXPECT_THAT(tree.children.at("Deep")->marker, Eq(false));
}

TEST(TrieRemoveTest, DISABLED_RemoveParentAndCompressWithSingleChild) {
  Trie tree;
  tree.children.emplace("Deep", new Node{true, nullptr, {}});
  tree.children.at("Deep")->children.emplace("sea", new Node{true, nullptr, {}});

  tree.Remove("Deep");
  EXPECT_THAT(tree.children, Contains(Key("Deepsea")));
  EXPECT_THAT(tree.children, Not(Contains(Key("Deep"))));
}

TEST(TrieRemoveTest, DISABLED_RemoveElementFromSecondLevel) {
  Trie tree;
  tree.children.emplace("On", new Node{});
  tree.children.at("On")->children.emplace("e", new Node{true, nullptr, {}});
  tree.children.at("On")->children.emplace("ce", new Node{true, nullptr, {}});
  tree.children.at("On")->children.emplace("ion", new Node{true, nullptr, {}});

  tree.Remove("Once");
  EXPECT_THAT(tree.children.at("On")->children, Not(Contains(Key("ce"))));
}

TEST(TrieRemoveTest, DISABLED_RemoveChildAndCompressWithParentLastChild) {
  Trie tree;
  tree.children.emplace("On", new Node{});
  tree.children.at("On")->children.emplace("e", new Node{true, nullptr, {}});
  tree.children.at("On")->children.emplace("ce", new Node{true, nullptr, {}});

  tree.Remove("One");
  EXPECT_THAT(tree.children, Contains(Key("Once")));
}
