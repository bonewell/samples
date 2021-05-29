#include <algorithm>
#include <chrono>
#include <fstream>
#include <iterator>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

class Top {
	public:
	    using Count = int;
	    struct Info {string_view word; Count count;};
	    using List = vector<Info>;
	    Top(int number) : number_{number} {}
	    void accumulate(string const& word);
	    List list() const;
	    
	private:
	    using Index = int;
	    struct Data {Index index; Count count;};
	    using Words = map<string, Data>; 
	    using WordIt = Words::iterator;
	    void up(WordIt const& wit);
	    int number_{10};
	    Words words_;
	    vector<WordIt> list_;
};

Top::List Top::list() const {
	List top;
	auto b = begin(list_);
	auto e = list_.size() > number_ ? begin(list_) + number_ : end(list_);
	transform(b, e, back_inserter(top), [](auto const& p) -> Info {
		return {p->first, p->second.count};
		});
	return top;
}
/*
void Top::up(Top::WordIt const& wit) {
	auto i = wit->second.index;
	while(i > 0 && list_[i]->second.count > list_[i-1]->second.count) {
		swap(list_[i], list_[i-1]);
		swap(list_[i]->second.index, list_[i-1]->second.index);
		i--;
	}
}
*/
void Top::up(Top::WordIt const& wit) {
	auto b = begin(list_);
	auto e = begin(list_) + wit->second.index;	
	while (b != e) {
		b = upper_bound(b, e, *e, [this](auto const& a, auto const& b) {
		return a->second.count > b->second.count;
	}); 
	    swap(*b, *e);
	    swap((*b)->second.index, (*e)->second.index);
	}
}

void Top::accumulate(string const& word) {
	auto wit = words_.find(word);
	Index i = list_.size();
	if (wit == end(words_)) {
		auto p = words_.emplace(word, Data{i, 0});
		if (p.second) {
		    wit = p.first;
		    list_.push_back(wit);
		}
	}
	wit->second.count++;
	up(wit);
}

ostream& operator<<(ostream& out, Top::Info const& info) {
	return out << info.word << '(' << info.count << ')';
}

ostream& operator<<(ostream& out, Top const& top) {
	auto infos = top.list();
	copy(begin(infos), end(infos), ostream_iterator<Top::Info>{out, " "});
	return out;
}
void test() {
	Top top{5};
/*	top.accumulate("one");
	cout << top << endl;
	top.accumulate("two");
	cout << top << endl;
	top.accumulate("two");
	cout << top << endl;
	top.accumulate("one");
	cout << top << endl;
	top.accumulate("two");
	cout << top << endl;
*/	
	ifstream ifile{"new.txt"};
	while (ifile)
	{
		string w;
		ifile >> w;
		top.accumulate(w);
	}
	cout << top << endl;
}


int main() {
	auto start_time = chrono::steady_clock::now();
	test();
	auto end_time = chrono::steady_clock::now();
	chrono::duration<double> diff_time = end_time - start_time;
	cout << "Time:" << diff_time.count() << endl;
	
	return 0;
}
