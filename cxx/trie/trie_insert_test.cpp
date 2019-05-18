#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "trie.h"

using ::testing::Contains;
using ::testing::Eq;
using ::testing::Key;
using ::testing::SizeIs;

TEST(TrieInsertTest, InsertIntoEmptyTree) {
  Trie tree;

  tree.Insert("One");

  EXPECT_THAT(tree.children, Contains(Key("One")));
}

TEST(TrieInsertTest, InsertTwoDifferentElements) {
  Trie tree;
  tree.children["One"] = new Node{true, nullptr, {}};

  tree.Insert("Two");

  EXPECT_THAT(tree.children, Contains(Key("Two")));
}

TEST(TrieInsertTest, InsertElementWithLongKey) {
  Trie tree;
  tree.children["In"] = new Node{true, nullptr, {}};

  tree.Insert("Inside");

  EXPECT_THAT(tree.children["In"]->children, SizeIs(1));
  EXPECT_THAT(tree.children["In"]->children, Contains(Key("side")));
}

TEST(TrieInsertTest, InsertTwoSimilarElements) {
  Trie tree;
  tree.children["One"] = new Node{true, nullptr, {}};

  tree.Insert("Once");

  ASSERT_THAT(tree.children, Contains(Key("On")));
  EXPECT_THAT(tree.children["On"]->children, Contains(Key("e")));
  EXPECT_THAT(tree.children["On"]->children, Contains(Key("ce")));
}

TEST(TrieInsertTest, InsertElementWithData) {
  Trie tree;
  auto data = new Data{};
  tree.Insert("Data", data);

  ASSERT_THAT(tree.children, Contains(Key("Data")));
  EXPECT_THAT(tree.children["Data"]->data, Eq(data));
}

TEST(TrieInsertTest, ElementInsertionSetsTrueMarker) {
  Trie tree;
  tree.Insert("One");

  ASSERT_THAT(tree.children, Contains(Key("One")));
  EXPECT_THAT(tree.children["One"]->marker, Eq(true));
}

TEST(TrieInsertTest, ElementInsertionSetsFalseMarker) {
  Trie tree;
  tree.children["One"] = new Node{true, nullptr, {}};

  tree.Insert("Once");

  ASSERT_THAT(tree.children, Contains(Key("On")));
  EXPECT_THAT(tree.children["On"]->marker, Eq(false));
}

TEST(TrieInsertTest, DeepInsertion) {
  Trie tree;
  tree.children["De"] = new Node{};
  tree.children["De"]->children["ep"] = new Node{true, nullptr, {}};
  tree.children["De"]->children["ad"] = new Node{true, nullptr, {}};

  tree.Insert("Deepwater");

  EXPECT_THAT(tree.children["De"]->children["ep"]->children, Contains(Key("water")));
}

TEST(TrieInsertTest, DeepInsertionOfSimilarElement) {
  Trie tree;
  tree.children["De"] = new Node{};
  tree.children["De"]->children["ep"] = new Node{true, nullptr, {}};
  tree.children["De"]->children["ad"] = new Node{true, nullptr, {}};

  tree.Insert("Death");

  ASSERT_THAT(tree.children["De"]->children, Contains(Key("a")));
  EXPECT_THAT(tree.children["De"]->children["a"]->children, Contains(Key("d")));
  EXPECT_THAT(tree.children["De"]->children["a"]->children, Contains(Key("th")));
}

TEST(TrieInsertTest, InsertionIsJustMark) {
  Trie tree;
  tree.children["On"] = new Node{};
  tree.children["On"]->children["e"] = new Node{true, nullptr, {}};
  tree.children["On"]->children["ce"] = new Node{true, nullptr, {}};

  tree.Insert("On");

  EXPECT_THAT(tree.children["On"]->marker, Eq(true));
}

TEST(TrieInsertTest, KeepChildrenForReplacedElement) {
  Trie tree;
  tree.children["On"] = new Node{};
  tree.children["On"]->children["e"] = new Node{true, nullptr, {}};
  tree.children["On"]->children["ce"] = new Node{true, nullptr, {}};

  tree.Insert("On");

  EXPECT_THAT(tree.children["On"]->children, Contains(Key("e")));
  EXPECT_THAT(tree.children["On"]->children, Contains(Key("ce")));
}

TEST(TrieInsertTest, InsertElementWithShortKey) {
  Trie tree;
  tree.children["Deepwater"] = new Node{true, nullptr, {}};

  tree.Insert("Deep");

  ASSERT_THAT(tree.children, Contains(Key("Deep")));
  EXPECT_THAT(tree.children["Deep"]->children, SizeIs(1));
  EXPECT_THAT(tree.children["Deep"]->children, Contains(Key("water")));
}
