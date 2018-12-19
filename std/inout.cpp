#include <iostream>
#include <string>

using namespace std;

struct Engine {
  string model;
  int power;
};

ostream& operator<<(ostream& out, const Engine& e) {
  return out << "{'" << e.model << "', " << e.power << "}";
}

istream& operator>>(istream& in, Engine& e) {
  char c;
  if (in >> c && c=='{' && in >> c && c=='\'') {
    string model;
    while (in.get(c) && c!='\'') {
      model += c;
    }

    if (in >> c && c==',') {
      int power = 0;
      if (in >> power >> c && c=='}') {
        e = {model, power};
	return in;
      }
    }
  }

  in.setstate(ios_base::failbit);
  return in;
}

int main() {
  Engine e;
  cin >> e;
  cout << e << "\n";
}
