//usr/bin/g++ --std=c++17 "$0" && ./a.out; exit
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
using namespace std;

struct Node{
   Node* next;
   Node* prev;
   int value;
   int key;
   Node(Node* p, Node* n, int k, int val):prev(p),next(n),key(k),value(val){};
   Node(int k, int val):prev(NULL),next(NULL),key(k),value(val){};
};

class Cache{

   protected:
   map<int,Node*> mp; //map the key to the node in the linked list
   int cp;  //capacity
   Node* tail; // double linked list tail pointer
   Node* head; // double linked list head pointer
   virtual void set(int, int) = 0; //set function
   virtual int get(int) = 0; //get function

};

class LRUCache : public Cache {
public:
    explicit LRUCache(int cap) {
        cp = cap;
        tail = nullptr;
        head = nullptr;
    }

    void set(int key, int value) override {
        if (mp.find(key) != end(mp)) {
            auto c = mp[key];
            if (c->prev) {
                if (!c->next) tail = c->prev;
                c->prev->next = c->next;
                c->prev = nullptr;
                c->next = head;
                head = c;
            }
            c->value = value;
        }
        else {
            Node* n = new Node{nullptr, head, key, value};
            mp[key] = n;
            if (head)
                head->prev = n;
            head = n;

            if (!tail)
                tail = n;

            if (mp.size() > cp) {
                mp.erase(tail->key);
                auto p = tail->prev;
                p->next = nullptr;
                delete tail;
                tail = p;
            }
        }
    }

    int get(int key) override {
        return (mp.find(key) != end(mp)) ? mp[key]->value : -1;
    }
};

int main() {
   int n, capacity,i;
   cin >> n >> capacity;
   LRUCache l(capacity);
   for(i=0;i<n;i++) {
      string command;
      cin >> command;
      if(command == "get") {
         int key;
         cin >> key;
         cout << l.get(key) << endl;
      }
      else if(command == "set") {
         int key, value;
         cin >> key >> value;
         l.set(key,value);
      }
   }
   return 0;
}
