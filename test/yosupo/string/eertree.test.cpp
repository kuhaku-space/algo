// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/eertree
#include <iostream>
#include <string>
#include <vector>
#include "string/palindromic_tree.hpp"

int main() {
    std::string s;
    std::cin >> s;

    PalindromicTree pt;
    int len = s.size();
    std::vector<int> active(len);
    for (int j = 0; j < len; ++j) active[j] = pt.add(s[j]);

    int total = pt.size();  // 仮想根 2 つを含む
    int n = total - 2;

    std::cout << n << '\n';
    // 内部番号 i (>=2) は問題番号 i-1（ODD 根=0→-1, EVEN 根=1→0）。
    // parent は両端 1 文字を除いた回文ノード（len 1→ODD 根, len 2→EVEN 根）。
    for (int i = 2; i < total; ++i) {
        auto *nd = pt.get_node(i);
        std::cout << nd->parent - 1 << ' ' << nd->suffix_link - 1 << '\n';
    }
    for (int j = 0; j < len; ++j) { std::cout << active[j] - 1 << (j == len - 1 ? '\n' : ' '); }
    return 0;
}
