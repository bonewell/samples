#include <memory>
#include <iostream>
#include <boost/type_index.hpp>

using namespace std;
using boost::typeindex::type_id_with_cvr;

auto del = [](int* p) { 
  cout << "del\n";
  delete p;
};

void dele(int* p) { 
  cout << "dele\n";
  delete p;
}

int main() {
  unique_ptr<int> ptr{new int(6)};
  cout << sizeof(ptr) << " - " << type_id_with_cvr<decltype(ptr)>().pretty_name() << "\n";
  
  unique_ptr<int, decltype(del)> ptrl{new int(6), del};
  cout << sizeof(ptrl) << " - " << type_id_with_cvr<decltype(ptrl)>().pretty_name() << "\n";
  
  unique_ptr<int, void(*)(int*)> ptrf{new int(6), dele};
  cout << sizeof(ptrf) << " - " << type_id_with_cvr<decltype(ptrf)>().pretty_name() << "\n";
  
  unique_ptr<int, void(*)(int*)> ptr1{new int(6), del};
  ptrf = move(ptr1);
  unique_ptr<int, decltype(del)> ptr2{new int(3), del};
//   ptrl = move(ptr2); compile error
  
  shared_ptr<int> sptr{new int(7)};
  cout << sizeof(sptr) <<  " - " << type_id_with_cvr<decltype(sptr)>().pretty_name() << "\n";
  
  weak_ptr<int> wptr{sptr};
  cout << sizeof(wptr) <<  " - " << type_id_with_cvr<decltype(wptr)>().pretty_name() << "\n";  
}
