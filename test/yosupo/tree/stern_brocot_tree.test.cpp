// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/stern_brocot_tree
#include <cstdint>
#include <iostream>
#include <string>
#include "template/sonic.hpp"
#include "tree/stern_brocot_tree.hpp"

using sbt = stern_brocot_tree;

sbt::path read_path() {
    int k;
    std::cin >> k;
    sbt::path p(k);
    for (auto &[c, n] : p) std::cin >> c >> n;
    return p;
}

int main(void) {
    int t;
    std::cin >> t;
    while (t--) {
        std::string query;
        std::cin >> query;
        if (query == "ENCODE_PATH") {
            std::int64_t a, b;
            std::cin >> a >> b;
            auto p = sbt::encode({a, b});
            std::cout << p.size();
            for (auto [c, n] : p) std::cout << ' ' << c << ' ' << n;
            std::cout << '\n';
        } else if (query == "DECODE_PATH") {
            auto f = sbt::decode(read_path());
            std::cout << f.p << ' ' << f.q << '\n';
        } else if (query == "LCA") {
            std::int64_t a, b, c, d;
            std::cin >> a >> b >> c >> d;
            auto f = sbt::lca({a, b}, {c, d});
            std::cout << f.p << ' ' << f.q << '\n';
        } else if (query == "ANCESTOR") {
            std::int64_t k, a, b;
            std::cin >> k >> a >> b;
            auto f = sbt::ancestor(k, {a, b});
            if (f.p == 0 && f.q == 0) std::cout << -1 << '\n';
            else std::cout << f.p << ' ' << f.q << '\n';
        } else if (query == "RANGE") {
            std::int64_t a, b;
            std::cin >> a >> b;
            auto [lo, hi] = sbt::from_fraction({a, b}).range();
            std::cout << lo.p << ' ' << lo.q << ' ' << hi.p << ' ' << hi.q << '\n';
        }
    }

    return 0;
}
