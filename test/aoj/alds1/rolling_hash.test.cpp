// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/14/ALDS1_14_B
#include "string/rolling_hash.hpp"
#include <iostream>
#include <string>

int main(void) {
    std::string s;
    std::cin >> s;

    rolling_hash rh(s);
    std::string t;
    std::cin >> t;
    for (auto e : rh.search(t)) std::cout << e << std::endl;

    return 0;
}
