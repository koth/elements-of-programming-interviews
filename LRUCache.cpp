// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <iostream>
#include <cassert>
#include <list>
#include <unordered_map>
#include <utility>

using std::cout;
using std::endl;
using std::list;
using std::pair;
using std::unordered_map;

// @include
template <typename ISBNType, typename PriceType, size_t capacity>
class LRUCache {
 public:
  bool lookup(const ISBNType &isbn, PriceType* price) {
    auto it = cache_.find(isbn);
    if (it == cache_.end()) {
      return false;
    }

    *price = it->second.second;
    moveToFront(isbn, it);
    return true;
  }

  void insert(const ISBNType &isbn, const PriceType &price) {
    auto it = cache_.find(isbn);
    if (it != cache_.end()) {
      moveToFront(isbn, it);
    } else {
      // Remove the least recently used.
      if (cache_.size() == capacity) {
        cache_.erase(data_.back());
        data_.pop_back();
      }

      data_.emplace_front(isbn);
      cache_[isbn] = {data_.begin(), price};
    }
  }

  bool erase(const ISBNType &isbn) {
    auto it = cache_.find(isbn);
    if (it == cache_.end()) {
      return false;
    }

    data_.erase(it->second.first);
    cache_.erase(it);
    return true;
  }

 private:
  typedef unordered_map<ISBNType,
                        pair<typename list<ISBNType>::iterator,
                             PriceType>> Table;

  // Move the most recent accessed item to the front.
  void moveToFront(const ISBNType &isbn, const typename Table::iterator &it) {
    data_.erase(it->second.first);
    data_.emplace_front(isbn);
    it->second.first = data_.begin();
  }

  Table cache_;
  list<ISBNType> data_;
};
// @exclude

int main(int argc, char *argv[]) {
  LRUCache<int, int, 3> c;
  cout << "c.insert(1, 1)" << endl;
  c.insert(1, 1);
  cout << "c.insert(1, 10)" << endl;
  c.insert(1, 10);
  int val;
  cout << "c.lookup(2, val)" << endl;
  assert(!c.lookup(2, &val));
  cout << "c.lookup(1, val)" << endl;
  assert(c.lookup(1, &val));
  assert(val == 1);
  c.erase(1);
  assert(!c.lookup(1, &val));
  return 0;
}
