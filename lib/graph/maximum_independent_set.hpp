#pragma once
#include "graph/graph.hpp"
#include "template/template.hpp"

/**
 * @brief 最大独立集合
 * @see https://www.slideshare.net/wata_orz/ss-12131479
 *
 * @tparam T 辺の重みの型
 * @param graph グラフ
 * @return std::vector<int> 最大独立集合
 */
template <class T>
std::vector<int> maximum_independent_set(const Graph<T> &graph) {
    int n = graph.size();
    std::vector<std::int64_t> g(n);
    for (auto es : graph) {
        for (auto e : es) {
            g[e.from()] |= 1LL << e.to();
        }
    }

    std::int64_t mv = 0, v = 0;
    int msz = 0, sz = 0;
    auto f = [&](auto self, std::int64_t used) {
        if (used == (1LL << n) - 1) {
            if (chmax(msz, sz)) {
                mv = v;
            }
            return;
        }
        int deg = 0, x = -1;
        for (int i = 0; i < n; ++i) {
            if (used >> i & 1) continue;
            int d = __builtin_popcountl(~used & g[i]);
            if (d <= 1) {
                x = i;
                break;
            }
            if (chmax(deg, d)) x = i;
        }
        used |= 1LL << x;

        if (deg > 2) {
            self(self, used);
        }

        v |= 1LL << x;
        ++sz;
        used |= g[x];
        self(self, used);
        v &= ~(1LL << x);
        --sz;
    };
    f(f, 0);

    std::vector<int> res;
    for (int i = 0; i < n; ++i) {
        if (mv >> i & 1) res.emplace_back(i);
    }
    return res;
}
