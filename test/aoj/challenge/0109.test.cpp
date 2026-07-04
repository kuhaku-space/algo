// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/0109
#include <iostream>
#include <string>
#include "string/parser.hpp"

int main() {
    int n;
    std::cin >> n;
    while (n--) {
        std::string s;
        std::cin >> s;
        // 式は '=' で終わるので末尾を落とす
        if (!s.empty() && s.back() == '=') s.pop_back();
        std::cout << eval_expr<long long>(s) << '\n';
    }
    return 0;
}
