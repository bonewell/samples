#include "classb.h"

// clang++ -c classb.cpp
// clang++ -c main.cpp
// clang++ classb.o main.o here it will be error of undefined symbol

int main() {
  double y = do_that(4.2);
  int x = do_those(5);
}