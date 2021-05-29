#include <iostream>
#include <vector>
using namespace std;

template<typename I, typename T>
constexpr I bfind(I bi, I ei, T v) {
	auto b = bi;
	auto e = ei;
	while (b != e) {
	    auto m = b + (e - b)/2;
	    if (*m == v)
	        return m;
	    if (*m > v) e = m;
	    if (*m < v) b = m + 1;
	}
	return ei;
}

template<class C>
constexpr typename C::iterator bfind(C& data, typename C::value_type v) {
	return bfind(data.begin(), data.end(), v);
}

template<typename T>
constexpr void test(vector<T> sdata, T v){
    auto ret = bfind(sdata, v);

    if (ret != sdata.end())
	    cout << *ret << endl;
	else
	    cout << "Not found\n";
}

int main(){
	test({1,2,3,4,5,6,7,8,9}, 0);
	test({1,2,3,4,5,6,7,8,9}, 3);
	test({2,3,4,5,6,7,8,9}, 7);
	test({1,2,3,4,5,6,7,8,9}, 10);
	test({1,2,3,5,8,13,21}, 1);
	test({1,2,3,5,8,13,21}, 5);
	test({1,2,3,5,8,13,21}, 8);
	test({1,2,3,5,8,13,21}, 21);
	test({1,2,3,5,8,13,21}, -7);
	test({1,2,3,5,8,13,21}, 4);
	test({1,2,3,5,8,13,21}, 22);

    return 0;
}
