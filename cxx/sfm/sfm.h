#include <memory>

template<class T>
class State {
 public:
  using sfm_t = T;
};

template<class T>
class SFM {
 protected:
  std::unique_ptr<T> state_;
 public:
  void setState(std::unique_ptr<T> state) {
    std::swap(state_, state);
  }
};
