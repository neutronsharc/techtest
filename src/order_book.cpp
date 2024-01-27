//
// Created by shawn.ouyang on 1/12/2024.
//
#include <iostream>
#include <algorithm>
#include <queue>
#include <sstream>
#include <unordered_map>
#include <map>
#include <set>

using namespace std;

/// 1. order book.
struct Order {
  enum Op {
	buy = 0,
	sell = 1,
  };
  Op op;
  int price;
  int quantity;
  int id;

  static int next_id_;

  Order(Op op_, int p, int q) {
	price = p;
	quantity = q;
  }

  std::string ToString() const {
	std::stringstream ss;
	ss << "[price=" << price << ", q=" << quantity << ", id=" << id << "]";
	return ss.str();
  }
};

class OrderBook {
public:
  OrderBook() {
  }

  // return order id.
  int AddOrder(Order& o) {
	o.id = Order::next_id_++;
	auto it = price_map_.find(o.price);
	if (it != price_map_.end()) {
	  it->second.push_back(o);
	} else {
	  price_map_.insert({o.price, {o}});
	}
	return true;
  }

  void Show() {
	auto it = price_map_.rbegin();
	cout << "price=" << it->first << "orders = " <<  it->second.size() << endl;
	for (auto& o : it->second) {
	  cout << endl << o.ToString();
	}
  }

private:
  std::map<int, std::vector<Order>> price_map_;
  std::map<int, Order> id_map_;
  std::map<Order*, Order> t_;
};

int Order::next_id_ = 1;

void OrderBookTest() {
  OrderBook book;
  Order o1(Order::Op::buy, 123, 10);
  Order o2(Order::buy, 15, 8);
  Order o3(Order::buy, 15, 4);
  Order o4(Order::buy, 156, 42);
  Order o5(Order::buy, 156, 467);

  book.AddOrder(o1);
  book.AddOrder(o2);
  book.AddOrder(o3);
  book.AddOrder(o4);
  book.AddOrder(o5);

  book.Show();
}
