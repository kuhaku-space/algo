// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/number_of_substrings
#include <iostream>
#include <string>
#include <vector>
#include "string/suffix_tree.hpp"

int main() {
    std::string s;
    std::cin >> s;

    suffix_tree<char> st(s);

    long long ans = 0;
    for (size_t i = 1; i < st.nodes.size(); ++i) {
        ans += st.nodes[i].len();
    }

    std::cout << ans << std::endl;

    return 0;
}
