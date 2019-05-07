#ifndef REQUESTED_CATEGORIES_H_
#define REQUESTED_CATEGORIES_H_

#include <functional>
#include <mutex>
#include <set>
#include "types.h"

/**
 * Represents list of requested categories.
 * The list can be used in multi-threads environment safely.
 * The list does not allow duplicates.
 */
class RequestedCategories {
 public:
  /**
   * Adds category into the list if the list doesn't already contain a category.
   * @param category to add into the list
   */
  void Add(Category category);

  /**
   * Executes the function for every category in the list
   * @param func function to run
   */
  void DoForEach(std::function<void(Category)> func) const;

  /**
   * Checks whether category presented in the list.
   * @param category to check
   */
  bool IsPresented(Category category) const;

  /**
   * Removes category from the list if one exists.
   * @param category to remove from the list
   */
  void Remove(Category category);

  /**
   * Removes all categories from the list
   */
  void Clear();

 private:
  std::set<Category> categories_;
  mutable std::mutex mutex_;
};

#endif  // REQUESTED_CATEGORIES_H_
