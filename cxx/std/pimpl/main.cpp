#include "pimpl.h"

int main() {
  Pimpl p;
  Pimpl pp;
  p = pp;
  
  Pimpl ppp;
  ppp = std::move(pp);
  
  p.print();

  SharedPimpl sp;
  SharedPimpl spp;
  sp = spp;
  
  SharedPimpl sppp;
  sppp = std::move(spp);
  
  sp.print();
}
