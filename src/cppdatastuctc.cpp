//
// Created by shawn.ouyang on 12/19/2023.
//

#include "string.h"

#include <iostream>
#include <algorithm>
#include <queue>
#include <sstream>
#include <unordered_map>
#include <map>
#include <set>

using namespace std;


template <typename S>
ostream& operator<<(ostream& os, const vector<S>& vector) {
  // Printing all the elements using <<
  os << "{";
  size_t i = 0;
  for (auto& element : vector) {
	os << element;
	i++;
	if (i < vector.size()) {
	  os << ",";
	}
  }
  os << "}";
  return os;
}


void Pq() {
  int a = (1 << 5) - 1;
  cout << "a=" << a << endl;
  auto cmp = [](const int& a, const int&b) {
    return a < b;
  };
  // std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
  std::priority_queue<int, std::vector<int>, decltype(cmp)> pq(cmp);

  std::vector<int> vals = {2, 6, 7, 15, 1, 5, 8, 24, 36, 14, 9};

  std::sort(vals.begin(), vals.end(), std::greater<int>());

  int k = 3;
  for (auto v : vals) {
    if (pq.size() < k) {
      pq.push(v);
    } else {
      if (v < pq.top()) {
        pq.pop();
        pq.push(v);
      }
    }
  }
  cout << "kth = " << pq.top() << endl;
}


////////////////////  map
void TestMap() {
  std::unordered_map<std::string, int> umap;
  umap["one"]++;
  umap["two"]++;
  umap["one"]++;

  for (const auto &it: umap) {
	std::cout << "key=" << it.first << " appeared " << it.second << " times" << endl;
  }

  auto comp = [](const std::string &s1, const std::string &s2) {
	return s1.size() < s2.size();
  };
  std::map<std::string, int, decltype(comp)> tmap(comp);  // ordered.
  tmap.insert({"one", 1});
  tmap.insert({"tw", 2});
  tmap.insert({"three", 3});
  tmap.insert({"four", 4});

  cout << "ordered map" << endl;
  for (auto &it: tmap) {
	cout << "key=" << it.first << ", value=" << it.second << endl;
  }
}


struct Rect {
  enum Side {
	kBuy,
	kSell,
  };
  int x_begin;
  int x_end;
  int h;  // height

  Side side;

  Rect() {}
  Rect(int x1, int x2, int _h)
	: x_begin(x1), x_end(x2), h(_h) {}

  std::string ToString() const {
	std::stringstream ss;
	ss << "[xbegin=" << x_begin << ", xend=" << x_end << ", h=" << h << "]";
	return ss.str();
  }
};

void MapTest1() {
  Rect r1(1, 5, 2);
  Rect r2(2, 20, 15);
  Rect r3(3, 8, 9);
  Rect r4(4, 6, 17);
  Rect r5(5, 9, 2);

  auto rect_comp = [](const Rect* r1, const Rect *r2) {
	return r1->h < r2->h;
  };

  std::map<Rect*, Rect*, decltype(rect_comp)> rmap(rect_comp);

  rmap.insert({&r1, &r1});
  rmap.insert({&r3, &r3});
  rmap.insert({&r2, &r2});
  rmap.insert({&r4, &r4});
  rmap.insert({&r5, &r5});

  std::cout << "map size=" << rmap.size() << std::endl;
  for (auto it = rmap.rbegin(); it != rmap.rend(); it++) {
	std::cout << "map last obj=" << it->first->ToString() << std::endl;
  }

  std::cout << "find r1=" << rmap.find(&r1)->second->ToString() << std::endl;
  std::cout << "find r5=" << rmap.find(&r5)->second->ToString() << std::endl;

  // set also sorts its elements.
  std::set<Rect*, decltype(rect_comp)> rset(rect_comp);
  rset.insert(&r1);
  rset.insert(&r2);
  rset.insert(&r3);
  rset.insert(&r4);
  rset.insert(&r5);

  std::cout << "set size=" << rset.size() << std::endl;
  std::cout << "set find r1=" << rmap.find(&r1)->second->ToString() << std::endl;
  std::cout << "set find r5=" << rmap.find(&r5)->second->ToString() << std::endl;
}


void CppDataPractice() {
  std::string s = "/a/b//../c//d/../e";
  std::stringstream ss(s);
  std::string tkn;
  while (std::getline(ss, tkn, '/')) {
    cout << tkn << endl;
    if (tkn.empty()) {
      continue;
    }
  }
  Pq();
}