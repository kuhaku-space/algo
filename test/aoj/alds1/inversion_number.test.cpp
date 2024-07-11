// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_5_D
#include "algorithm/inversion_number.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main(void) {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    std::copy_n(std::istream_iterator<int>(std::cin), n, std::begin(a));
    std::cout << inversion_number(a) << std::endl;

    return 0;
}
