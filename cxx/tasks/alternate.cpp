//usr/bin/g++ --std=c++17 "$0" && ./a.out; exit

#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

bool validate(const string& str) {
	for (int i = 0; i < str.length(); ++i) {
		if (str[i] == str[i+1]) return false;
	}
	return true;
}

int alternate(string s) {
    set<char> ss{begin(s), end(s)};
    vector<char> vs{begin(ss), end(ss)};

    int maximum = 0;
    for (int i = 0; i < vs.size() - 1; ++i) {
        for (int j = i + 1; j < vs.size(); ++j) {
            string str;
            copy_if(begin(s), end(s), back_inserter(str),
            	[a=vs[i], b=vs[j]] (char c) {
            		return c == a || c == b;
            });
            if (validate(str)) {
            	int size = str.length();
            	maximum = max(size, maximum);
            }
        }
    }
    return maximum;
}

int main()
{
	cout << alternate("ountjurntdarfqstkerfjxktexgtpplruxwpoqtehmksshkfpiegpfwlwxsnteocpsdjlvlryulhosngqytqfinhvemshfrpvgbruvvultzeucustjdlfamggakwxgvoqbwruilxfxnitxlzrvcvtgvosbzcvzxiytuurwazmgobhkidyaxjwukoaicrigaaatxqstibdvnqaoyqkwkpkpbzqttlrsdkpfopwyjyjiqnqfmzlzmqwulsypnbylvrjrwjcyyeqnbrqszqbhoetqvpkefsblprlvyebaruapeslvluryxnqmykwdpovhqxcptpcjpbsablgcxpqwgwrrpfnwzxrfjtuhwudzfafxrqpzqmywubdijblzkvrwxyhcokubkfefmmbgycbeldnzztezclaheufiqhfgadvgjjjrhbzfevxduibwzehccmvhsoquedmpunhdiqahemwcllzhkvsbhkjlesjoorzurwfibndvoztxyjafnmmtrmomrvrjdwukdislktndxfxyvenotpnmwqkfzoyjtrhddoweehwfmekvxhpyozoojdujguyjxc") << "\n";

	return 0;
}