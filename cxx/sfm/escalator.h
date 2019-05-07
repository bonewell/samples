#include "sfm.h"
#include <iostream>

class EscalatorState;

class Escalator : public SFM<EscalatorState> {
  public:
   Escalator();
   void run();
   void stop();
   void repair();
};

class EscalatorState : public State<Escalator> {
 public:
   virtual void run(sfm_t* sfm) { std::cout << "Couldn't run\n"; }
   virtual void stop(sfm_t* sfm) { std::cout << "Couldn't stop\n"; }
   virtual void repair(sfm_t* sfm) { std::cout << "Couldn't repair\n"; }
};

class Mounted final : public EscalatorState {
 public:
  virtual void run(sfm_t* sfm) override;
};

class Idle final : public EscalatorState {
 public:
  virtual void run(sfm_t* sfm) override;
  virtual void repair(sfm_t* sfm) override;
};

class Running final : public EscalatorState {
 public:
  virtual void stop(sfm_t* sfm) override;
};

class Repair final : public EscalatorState {
  public:
   virtual void run(sfm_t* sfm) override;
};
