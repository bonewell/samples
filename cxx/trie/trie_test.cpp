#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "trie.h"

using ::testing::Contains;
using ::testing::Eq;
using ::testing::Key;

TEST(TrieTest, InsertIntoEmptyTree) {
  Trie tree;
  tree.Insert("One");

  EXPECT_THAT(tree.children, Contains(Key("One")));
}

TEST(TrieTest, InsertTwoDifferentElements) {
  Trie tree;
  tree.Insert("One");
  tree.Insert("Two");

  EXPECT_THAT(tree.children, Contains(Key("One")));
  EXPECT_THAT(tree.children, Contains(Key("Two")));
}

TEST(TrieTest, InsertWhenBeginOfKeyExists) {
  Trie tree;
  tree.Insert("In");
  tree.Insert("Inside");

  EXPECT_THAT(tree.children, Contains(Key("In")));
  EXPECT_THAT(tree.children.at("In")->children, Contains(Key("side")));
}

TEST(TrieTest, InsertTwoSimilarElements) {
  Trie tree;
  tree.Insert("One");
  tree.Insert("Once");

  ASSERT_THAT(tree.children, Contains(Key("On")));
  EXPECT_THAT(tree.children.at("On")->children, Contains(Key("e")));
  EXPECT_THAT(tree.children.at("On")->children, Contains(Key("ce")));
}

TEST(TrieTest, InsertElementWithData) {
  Trie tree;
  auto data = new Data{};
  tree.Insert("Data", data);

  ASSERT_THAT(tree.children, Contains(Key("Data")));
  EXPECT_THAT(tree.children.at("Data")->data, Eq(data));
}

TEST(TrieTest, ElementInsertionSetsTrueMarker) {
  Trie tree;
  tree.Insert("One");

  ASSERT_THAT(tree.children, Contains(Key("One")));
  EXPECT_THAT(tree.children.at("One")->marker, Eq(true));
}

TEST(TrieTest, ElementInsertionSetsFalseMarker) {
  Trie tree;
  tree.Insert("One");
  tree.Insert("Once");

  ASSERT_THAT(tree.children, Contains(Key("On")));
  EXPECT_THAT(tree.children.at("On")->marker, Eq(false));
}

TEST(TrieTest, DeepInsertion) {
  Trie tree;
  tree.Insert("Deep");
  tree.Insert("Dead");
  tree.Insert("Deepwater");

  ASSERT_THAT(tree.children, Contains(Key("De")));
  ASSERT_THAT(tree.children.at("De")->children, Contains(Key("ep")));
  EXPECT_THAT(tree.children.at("De")->children.at("ep")->children, Contains(Key("water")));
}

TEST(TrieTest, DeepInsertionOfSimilarElement) {
  Trie tree;
  tree.Insert("Deep");
  tree.Insert("Dead");
  tree.Insert("Death");

  ASSERT_THAT(tree.children, Contains(Key("De")));
  ASSERT_THAT(tree.children.at("De")->children, Contains(Key("a")));
  EXPECT_THAT(tree.children.at("De")->children.at("a")->children, Contains(Key("d")));
  EXPECT_THAT(tree.children.at("De")->children.at("a")->children, Contains(Key("th")));
}
