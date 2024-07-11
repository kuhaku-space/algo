// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/zalgorithm
#include <iostream>
#include <string>
#include <vector>
#include "string/z_algorithm.hpp"

int main(void) {
    std::string s;
    std::cin >> s;
    auto ans = z_algorithm(s);
    for (int i = 0; i < (int)ans.size(); ++i)
        std::cout << ans[i] << (i == (int)ans.size() - 1 ? '\n' : ' ');

    return 0;
}
