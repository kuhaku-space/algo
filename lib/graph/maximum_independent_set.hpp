#pragma once
#include <bit>
#include <cstdint>
#include <vector>
#include "graph/graph.hpp"

/// @brief 最大独立集合
/// @see https://www.slideshare.net/wata_orz/ss-12131479
template <class T>
std::vector<int> maximum_independent_set(const Graph<T> &graph) {
    int n = graph.size();
    std::vector<std::uint64_t> g(n);
    for (auto es : graph) {
        for (auto e : es) g[e.from()] |= std::uint64_t(1) << e.to();
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
            int d = std::popcount(~used & g[i]);
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
        used |= g[x];
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
