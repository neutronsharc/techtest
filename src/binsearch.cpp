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
#include <vector>

using namespace std;

/// 1. a sequence, increase, then decrease, find the pivot point.
int FindPivot(std::vector<int>& arr, int begin, int end) {
  if (begin > end) {
	return -1;
  }
  if (begin == end) {
	return begin;
  }
  if (begin + 1 == end) {
	return arr[begin] > arr[end] ? begin : end;
  }

  int mid = (end + begin) / 2;
  // int midd = begin + (end - begin) / 2;   // both are ok.

  if (arr[mid - 1] < arr[mid] && arr[mid] > arr[mid + 1]) {
	return mid;
  } else if (arr[mid - 1] < arr[mid + 1]) {
	return FindPivot(arr, mid, end);  // (mid, end) is ok
  } else {
	return FindPivot(arr, begin, mid);  // (begin, mid - 1) is ok
  }
}


void BinSearchTest() {
  std::vector<int> arr{2,3,4,5,6,7,20,18,17,16,15};
  int pivot;
  pivot = FindPivot(arr, 0, arr.size() - 1);
  cout << "pivot = " << pivot << endl;

  arr.push_back(13);
  arr.push_back(12);
  arr.push_back(10);
  arr.push_back(9);
  arr.push_back(8);
  arr.push_back(7);
  pivot = FindPivot(arr, 0, arr.size() - 1);
  cout << "pivot2 = " << pivot << endl;
}
