// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/frequency_table_of_tree_distance
#include <cstdint>
#include <iostream>
#include <vector>
#include "fft/fft.hpp"
#include "graph/graph.hpp"
#include "tree/centroid_decomposition.hpp"

int main(void) {
    int n;
    std::cin >> n;
    Graph<void> g(n);
    g.input_edges(n - 1, 0);

    std::vector<std::int64_t> ans(n, 0);  // ans[d] = 距離 d の頂点対 (順序付き) の総数

    // dist の自己畳み込みを ans へ sign 倍して足し込む (conv[k] = 距離 k の順序付きペア数)。
    auto add_self_conv = [&](const std::vector<std::int64_t> &dist, int sign) {
        if (dist.empty()) return;
        auto conv = fft::convolution(dist, dist);
        for (int k = 1; k < (int)conv.size() && k < n; ++k) ans[k] += sign * conv[k];
    };

    std::vector<int> child_idx(n, -1);  // c 直下の子 -> dists の添字 (使用後に -1 へ戻す)
    centroid_decomposition<void> cd(g);
    cd.run([&](const centroid_decomposition<void>::component &c) {
        // c を通る同じ子部分木のパスは二重計上なので、各子部分木の距離分布を引く。
        // c 全体の距離分布 (c は depth 0) を足す。
        std::vector<std::int64_t> whole = {1};  // 重心自身 (depth 0)
        std::vector<std::vector<std::int64_t>> dists;
        std::vector<int> children;  // c 直下の子 (child_idx のリセット対象)
        for (int x : c.order) {
            if (x == c.centroid) continue;
            int t = c.top[x];  // x が属する c 直下の子
            if (child_idx[t] == -1) {
                child_idx[t] = (int)dists.size();
                dists.emplace_back();
                children.push_back(t);
            }
            auto &d = dists[child_idx[t]];
            int dx = c.dep[x];
            if (dx >= (int)d.size()) d.resize(dx + 1, 0);
            ++d[dx];
        }
        for (int t : children) child_idx[t] = -1;  // O(degree) でリセット
        for (auto &d : dists) {
            add_self_conv(d, -1);
            if (d.size() > whole.size()) whole.resize(d.size(), 0);
            for (int i = 0; i < (int)d.size(); ++i) whole[i] += d[i];
        }
        add_self_conv(whole, +1);
    });

    for (int d = 1; d < n; ++d) std::cout << ans[d] / 2 << (d == n - 1 ? '\n' : ' ');
    if (n == 1) std::cout << '\n';

    return 0;
}
