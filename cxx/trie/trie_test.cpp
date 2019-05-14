#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "trie.h"

using ::testing::Contains;
using ::testing::Eq;
using ::testing::Key;

TEST(TestTrie, InsertIntoEmptyTree) {
  Trie tree;
  tree.Insert("One");

  EXPECT_THAT(tree.children, Contains(Key("One")));
}

TEST(TestTrie, InsertTwoDifferentElements) {
  Trie tree;
  tree.Insert("One");
  tree.Insert("Two");

  EXPECT_THAT(tree.children, Contains(Key("One")));
  EXPECT_THAT(tree.children, Contains(Key("Two")));
}

TEST(TestTrie, InsertWhenBeginOfKeyExists) {
  Trie tree;
  tree.Insert("In");
  tree.Insert("Inside");

  EXPECT_THAT(tree.children, Contains(Key("In")));
  EXPECT_THAT(tree.children.at("In")->children, Contains(Key("side")));
}

TEST(TestTrie, InsertTwoSimilarElements) {
  Trie tree;
  tree.Insert("One");
  tree.Insert("Once");

  ASSERT_THAT(tree.children, Contains(Key("On")));
  EXPECT_THAT(tree.children.at("On")->children, Contains(Key("e")));
  EXPECT_THAT(tree.children.at("On")->children, Contains(Key("ce")));
}

TEST(TestTrie, InsertElementWithData) {
  Trie tree;
  auto data = new Data{};
  tree.Insert("Data", data);

  ASSERT_THAT(tree.children, Contains(Key("Data")));
  EXPECT_THAT(tree.children.at("Data")->data, Eq(data));
}

TEST(TestTrie, ElementInsertionSetsTrueMarker) {
  Trie tree;
  tree.Insert("One");

  ASSERT_THAT(tree.children, Contains(Key("One")));
  EXPECT_THAT(tree.children.at("One")->marker, Eq(true));
}

TEST(TestTrie, ElementInsertionSetsFalseMarker) {
  Trie tree;
  tree.Insert("One");
  tree.Insert("Once");

  ASSERT_THAT(tree.children, Contains(Key("On")));
  EXPECT_THAT(tree.children.at("On")->marker, Eq(false));
}

TEST(TestTrie, DISABLED_DeepInsertion) {
}
