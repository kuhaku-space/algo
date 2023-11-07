#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/DPL_1_D"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include "algorithm/lis.hpp"

int main(void) {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    std::copy_n(std::istream_iterator<int>(std::cin), n, std::begin(a));
    std::cout << longest_increasing_subsequence(a) std::endl;

    return 0;
}
