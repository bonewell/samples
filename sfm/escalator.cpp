#include "escalator.h"

void Mounted::run(sfm_t* sfm) {
  std::cout << "Current state: Mounted\n";
  sfm->setState(std::make_unique<Running>());
  std::cout << "Running\n";
}

void Idle::run(sfm_t* sfm) {
  std::cout << "Current state: Idle\n";
  sfm->setState(std::make_unique<Running>());
  std::cout << "Running\n";
}

void Idle::repair(sfm_t* sfm) {
  std::cout << "Current state: Idle\n";
  sfm->setState(std::make_unique<Repair>());
  std::cout << "Repair\n";
}

void Running::stop(sfm_t* sfm) {
  std::cout << "Current state: Running\n";
  sfm->setState(std::make_unique<Idle>());
  std::cout << "Idle\n";
}

void Repair::run(sfm_t* sfm) {
  std::cout << "Current state: Repair\n";
  sfm->setState(std::make_unique<Running>());
  std::cout << "Running\n";
}

Escalator::Escalator() {
  setState(std::make_unique<Mounted>());
}

void Escalator::run() {
  std::cout << "Try run\n";
  state_->run(this);
}

void Escalator::stop() {
  std::cout << "Try stop\n";
  state_->stop(this);
}

void Escalator::repair() {
  std::cout << "Try repair\n";
  state_->repair(this);
}

int main() {
  Escalator e1;
  e1.run();
  e1.repair();
  e1.stop();
  e1.repair();
  return 0;
}
