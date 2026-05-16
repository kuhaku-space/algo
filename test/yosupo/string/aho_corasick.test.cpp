// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/aho_corasick
#include "string/aho_corasick.hpp"
#include <iostream>
#include <string>
#include <vector>

int main() {
    int n;
    std::cin >> n;

    aho_corasick<26, 'a'> aho;
    std::vector<int> val(n);

    for (int i = 0; i < n; ++i) {
        std::string s;
        std::cin >> s;
        val[i] = aho.insert(s).back();
    }

    aho.build();
    std::vector<int> fail = aho.failures();
    int m = aho.size();
    std::vector<int> parent(m);
    for (int i = 0; i < m; ++i) {
        for (int x : aho.get_node(i).next_node) {
            if (x != -1) parent[x] = i;
        }
    }

    std::cout << m << '\n';
    for (int i = 1; i < m; ++i) std::cout << parent[i] << ' ' << fail[i] << '\n';
    for (int i = 0; i < n; ++i) std::cout << val[i] << (i == n - 1 ? '\n' : ' ');

    return 0;
}
