// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/rooted_tree_isomorphism_classification
#include <cstdint>
#include <iostream>
#include <vector>
#include "algorithm/compress.hpp"
#include "random/zobrist_hash.hpp"

int main(void) {
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> children(n);
    for (int i = 1; i < n; ++i) {
        int p;
        std::cin >> p;
        children[p].emplace_back(i);
    }

    ZobristHash<std::uint64_t> zh;
    std::vector<std::uint64_t> raw_hash(n);
    for (int v = n - 1; v >= 0; --v) {
        std::uint64_t combined = 0;
        for (int c : children[v]) combined += zh(raw_hash[c]);
        raw_hash[v] = combined;
    }

    coordinate_compression<std::uint64_t> cc(raw_hash);
    auto id = cc.compress(raw_hash);

    std::cout << cc.size() << '\n';
    for (int i = 0; i < n; ++i) std::cout << id[i] << " \n"[i == n - 1];

    return 0;
}
