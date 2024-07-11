// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/DPL_1_D
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include "algorithm/lis.hpp"

int main(void) {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int &e : a) std::cin >> e;
    std::cout << longest_increasing_subsequence(a) << std::endl;

    return 0;
}
