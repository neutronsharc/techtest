//
// Created by shawn on 11/4/23.
//

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <unordered_map>
#include <climits>
#include <map>

using namespace std;

// Test ways to do combination / permutations

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

int GetSubsetWithDup(vector<int>& in, int n, int in_pos, vector<int>& subset, vector<vector<int> >& results) {
  if (in_pos == n) {
	results.push_back(subset);
	cout << subset << endl;
	return 1;
  }
  int range = 1;  // how many duplicates from current pos, including itself.
  for (int i = in_pos; i < n - 1; i++) {
	if (in[i] == in[i + 1]) {
	  range++;
	} else {
	  break;
	}
  }

  int cnt = 0;
  for (int i = 0; i <= range; i++) {
	// Elem [pos] repeats time= (0, 1, ... range).
	for (int j = 0; j < i; j++) {
	  subset.push_back(in[in_pos + j]);
	}
	cnt += GetSubsetWithDup(in, n, in_pos + range, subset, results);

	// Rm in[pos] element from the result vector. # of instances of this element is (0, 1, 2, ... range)
	for (int j = 0; j < i; j++) {
	  subset.pop_back();
	}
  }

  return cnt;
}

vector<vector<int> > AllSubsetWithDup(vector<int> arr, int n) {
  std::sort(arr.begin(), arr.end());

  vector<vector<int> > results;
  vector<int> subset;
  int num = GetSubsetWithDup(arr, n, 0, subset, results);
  cout << "has " << num << " subsets" << endl;

  // sort the vectors. result will be like:  {{},{1},{1,2},{1,2,2},{2},{2,2}}
  std::sort(results.begin(), results.end(), [](const std::vector<int> &a, const std::vector<int> &b) {
	// return true if "a" comes before "b" in the order.
	if (a.empty() && b.empty()) {
	  return true;
	}
	if (a.empty() && !b.empty()) {
	  return true;
	}
	if (!a.empty() && b.empty()) {
	  return false;
	}
	int len = std::min<int>(a.size(), b.size());
	for (int i = 0; i < len; i++) {
	  if (a[i] < b[i]) {
		return true;
	  } else if (a[i] > b[i]) {
		return false;
	  }
	}
	return a.size() < b.size();
  });
  cout << results << endl;
  return results;
}

// Return: number of combinations produced.
int AllSubset(std::vector<int>* in, int N, int in_pos, std::vector<int>*out) {
  if (in_pos == N) { // have finished exploring the in-vector.
	cout << *out << endl;
	return 1;
  }
  int cnt = 0;

  // not include current element
  cnt += AllSubset(in, N, in_pos + 1, out);

  // include current element.
  out->push_back(in->at(in_pos));
  cnt += AllSubset(in, N, in_pos + 1, out);
  out->pop_back();  // must do pop_back() here, otherwise the current elements will
  // be cumulated to subsequent results.

  return cnt;
}


//// max sum path:
struct TNode {
  int data;
  TNode *left, *right;

  TNode(int v) {
	data = v;
	left = right = nullptr;
  }
};


// Return the max-path-sum that starts from root "node", and ends at a special node.
// The "special node" is a node that's connected to exactly one other node.
int GetMaxPathSum(TNode* node, int* max_sum) {
  if (!node) {
	return 0;
  }

  int lsum = GetMaxPathSum(node->left, max_sum);
  int rsum = GetMaxPathSum(node->right, max_sum);

  int max_path = std::max(lsum + node->data, rsum + node->data);

  if (node->left || node->right) {
	*max_sum = std::max(*max_sum, lsum + node->data + rsum);
  }

  return max_path;
}

void TTest1() {
  TNode root(6), left(-9), right(-10);
  root.left = &left;
  root.right = &right;

  int maxsum = INT_MIN;
  int maxp = GetMaxPathSum(&root, &maxsum);

  // if the "root" misses one subtree, then the root node itself can be a special node.
  if (!root.left || !root.right) {

	maxsum = std::max(maxsum, maxp);
  }
  cout << "max path sum=" << maxsum << endl;
}




/////////////// test an interval overlapping length
struct Interval {
  int xbegin;
  int xend;
  int length;

  Interval() {}

  Interval operator+(const Interval &i) const {
	Interval itv;
	itv.xbegin = std::min(xbegin, i.xbegin);
	itv.xend = std::max(xend, i.xend);
	itv.length = itv.xend - itv.xbegin;
	return itv;
  }

  std::string ToString() const {
	char msg[200];
	snprintf(msg, sizeof(msg) - 1, "[begin=%d,end=%d,len=%d]", xbegin, xend, length);
	return std::string(msg);
  }

  Interval(int x1, int x2) {
	xbegin = x1;
	xend = x2;
	length = x2 - x1;
  }
};

void TestInterval() {
  Interval v1(1, 6);
  Interval v2(3, 9);
  auto v3 = v1 + v2;
  std::cout << "v3=" << v3.ToString() << std::endl;
}




//////////////////////////////

void Combination() {
  TestInterval();

  int v1 = 15 % 6;
  int v2 = -3 % 5;  // -3
  int v3 = -6 % 3;  // 0
  int v4 = -5 % 2;  // -1
  int v5 = ((-13 % 3) + 3) % 3;  // -1 => 1
  int v6 = 13 % -3;  // 1
  int v7 = -13 % -3;  // -1

  TTest1();

  vector<int> arr = {2, 1, 2, 3};
  AllSubsetWithDup(arr, arr.size());
//  vector<int> arr = {2 ,1, 2};

  std::vector<int> out;
  int cnt = AllSubset(&arr, arr.size(), 0, &out);
  cout << "found " << cnt << "combinations" << endl;
}

