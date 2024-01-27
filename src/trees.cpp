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
#include <stack>
#include <cassert>

using namespace std;


//// 2.  Inorder array and bin-tree.

struct Node {  // tree node.
  int val;
  Node *left, *right;
  Node() {
	val = 0;
	left = right = nullptr;
  }
};

void InitInOrder(std::stack<Node*>& stk, Node* root) {
  Node* t = root;
  while (t) {
	stk.push(t);
	t = t->left;
  }
}

Node* GetNextNode(std::stack<Node*>& stk) {
  if (stk.empty()) {
	return nullptr;
  }
  auto node = stk.top();
  stk.pop();

  auto t = node->right;  // store right subtree to stk;
  InitInOrder(stk, t);

  return node;
}

void SortedArrayToBst(std::vector<int>& vec) {
  int num_nodes = vec.size();

  std::vector<Node> tnodes(num_nodes + 1);  // need N+1 nodes for the tree idx [1, N] is used, node[0] is not used.

  // init the tree nodes.
  for (int i = 1; i <= num_nodes / 2; i++) {  // => must use i <= num/2, otherwise the tree may miss a node.
	int left = i * 2;
	int right = i * 2 + 1;
	if (left <= num_nodes) {
	  tnodes[i].left = &tnodes[left];
	}
	if (right <= num_nodes) {
	  tnodes[i].right = &tnodes[right];
	}
  }

  // in-order traverse.
  Node* root = &tnodes[1];
  std::stack<Node*> stk;

  // in-order traverse the tree, prepare stk.
  InitInOrder(stk, root);

  int i = 0;
  int tnode_num = 0;
  for (auto node = GetNextNode(stk); node; node = GetNextNode(stk)) {
	node->val = vec[i];
	cout << "vec[" << i << "] = " << vec[i] << endl;
	tnode_num++;
	i++;
  }
  assert(tnode_num == num_nodes);  //   "mismatched node number");

  // in-order traverse the tree, prepare stk.
  InitInOrder(stk, root);
  i = 0;
  std::cout << "in-order tree:" << std::endl;
  for (auto node = GetNextNode(stk); node; node = GetNextNode(stk)) {
	std::cout << "[" << i << "]: " << node->val << std::endl;
	i++;
  }
}

void TestSortArrayToBst() {
  std::vector<int> vec = {1,2,3,4,5,6,7,8,9,10,12,18,21,35,56,77,89,102};
  SortedArrayToBst(vec);
}
