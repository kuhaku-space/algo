#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"
#include "string/suffix_array.hpp"
#include <iostream>
#include <string>
#include <vector>

int main(void) {
    std::string s;
    std::cin >> s;
    auto ans = suffix_array(s);
    for (int i = 0; i < (int)ans.size(); ++i)
        std::cout << ans[i] << (i == (int)ans.size() - 1 ? '\n' : ' ');

    return 0;
}
