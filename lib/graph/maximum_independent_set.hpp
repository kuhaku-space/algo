#pragma once
#include <bit>
#include <cstdint>
#include <vector>
#include "graph/graph.hpp"

/// @brief 最大独立集合
/// @see https://www.slideshare.net/wata_orz/ss-12131479
/// @tparam G グラフ型（`list_graph<T>` / `csr_graph<T>` のいずれでも可）
template <graph_type G>
std::vector<int> maximum_independent_set(const G &g) {
    int n = g.size();
    std::vector<std::uint64_t> adj(n);
    for (int i = 0; i < n; ++i) {
        for (auto &e : g[i]) adj[e.from()] |= std::uint64_t(1) << e.to();
    }

    std::uint64_t max_v = 0, v = 0;
    int max_sz = 0, sz = 0;
    auto f = [&](auto self, std::uint64_t used) -> void {
        if (used == (std::uint64_t(1) << n) - 1) {
            if (max_sz < sz) max_sz = sz, max_v = v;
            return;
        }
        int deg = 0, x = -1;
        for (int i = 0; i < n; ++i) {
            if (used >> i & 1) continue;
            int d = std::popcount(~used & adj[i]);
            if (d <= 1) {
                x = i;
                break;
            }
            if (deg < d) deg = d, x = i;
        }
        used |= std::uint64_t(1) << x;

        if (deg > 2) self(self, used);

        v ^= std::uint64_t(1) << x;
        ++sz;
        used |= adj[x];
        self(self, used);
        v ^= std::uint64_t(1) << x;
        --sz;
    };
    f(f, 0);

    std::vector<int> res;
    for (int i = 0; i < n; ++i) {
        if (max_v >> i & 1) res.emplace_back(i);
    }
    return res;
}
