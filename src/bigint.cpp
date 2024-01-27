//
// Created by shawn.ouyang on 1/12/2024.
//
#include "string.h"

#include <iostream>
#include <algorithm>
#include <queue>
#include <sstream>

using namespace std;

void BigIntMulti() {
  std::string s1 = "12345678";
  std::string s2 = "23456789";

  int len1 = 8, len2 = 8;
  int len3 = len1 + len2;  // max result len=len1+len2
  char res[len3 + 1];  // include ending \0.
  memset(res, 0, len3 + 1);

  for (int i = len1 - 1; i >= 0; i--) {
	for (int j = len2 - 1; j >= 0; j--) {
	  int x = (s1[i] - '0') * (s2[j] - '0');
	  res[i + j + 1] += x;
	  res[i + j] += res[i + j + 1] / 10;
	  res[i + j + 1] %= 10;
	}
  }
  for (int i = 0; i < len3; i++) {
	res[i] += '0';
  }
  // 289589963907942
  int i = 0;  // rm leading '0's.
  std::string ss(res);
  while (res[i] == '0') {
	i++;
  }
  ss = ss.substr(i);
  cout << s1 << " * " << s2 << " = " << ss;
}