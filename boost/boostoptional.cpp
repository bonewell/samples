#include <iostream>
#include <string>
#include <boost/optional.hpp>

using namespace std;

int main() {
        boost::optional<std::string> str;// = boost::make_optional(true, std::string("abc"));

        if (!str) {
            std::cout << "false" << std::endl;
	} else {
            std::cout << "true" << std::endl;
	    std::cout << *str << std::endl;
	}

	return 0;
}
