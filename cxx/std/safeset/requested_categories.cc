#include "requested_categories.h"

#include <algorithm>

void RequestedCategories::Add(Category category) {
  std::lock_guard<std::mutex> guard(mutex_);
  categories_.insert(category);
}

bool RequestedCategories::IsPresented(Category category) const {
  std::lock_guard<std::mutex> guard(mutex_);
  return categories_.count(category) == 1;
}

void RequestedCategories::Remove(Category category) {
  std::lock_guard<std::mutex> guard(mutex_);
  categories_.erase(category);
}

void RequestedCategories::DoForEach(std::function<void(Category)> func) const {
  std::lock_guard<std::mutex> guard(mutex_);
  std::for_each(std::begin(categories_), std::end(categories_), func);
}

void RequestedCategories::Clear() {
  std::lock_guard<std::mutex> guard(mutex_);
  categories_.clear();
}
