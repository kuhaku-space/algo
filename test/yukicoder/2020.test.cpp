// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/2020
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include "binary_tree/fenwick_tree.hpp"
#include "graph/graph.hpp"
#include "string/trie.hpp"
#include "tree/hld.hpp"

int main() {
    int n;
    std::cin >> n;

    Trie<26, 'a'> trie;
    std::vector<int> pos(n);
    std::vector<std::vector<int>> init_path(n);
    for (int i = 0; i < n; ++i) {
        std::string s;
        std::cin >> s;
        init_path[i] = trie.insert(s);
        pos[i] = init_path[i].empty() ? 0 : init_path[i].back();
    }

    int q;
    std::cin >> q;
    std::vector<int> qtype(q), qx(q), qadd(q, -1);
    for (int i = 0; i < q; ++i) {
        std::cin >> qtype[i] >> qx[i];
        --qx[i];
        if (qtype[i] == 1) {
            char c;
            std::cin >> c;
            int nid = trie.add(pos[qx[i]], c);
            qadd[i] = nid;
            pos[qx[i]] = nid;
        }
    }

    int m = trie.size();
    Graph<int> g(m);
    for (int v = 0; v < m; ++v) {
        const auto node = trie.get_node(v);
        for (int c = 0; c < 26; ++c) {
            int u = node.next_node[c];
            if (u != -1) g.add_edges(v, u);
        }
    }
    heavy_light_decomposition hld(g, 0);

    fenwick_tree<std::int64_t> bit(m);
    auto point_add = [&](int v, int x) { bit.add(hld.get(v), x); };
    auto path_sum = [&](int v) {
        std::int64_t res = 0;
        hld.for_each(0, v, [&](int l, int r) { res += bit.sum(l, r); });
        res -= bit[hld.get(0)];
        return res;
    };

    std::vector<int> cur(n);
    for (int i = 0; i < n; ++i) {
        for (int v : init_path[i]) point_add(v, 1);
        cur[i] = init_path[i].empty() ? 0 : init_path[i].back();
    }

    for (int i = 0; i < q; ++i) {
        if (qtype[i] == 1) {
            point_add(qadd[i], 1);
            cur[qx[i]] = qadd[i];
        } else {
            std::cout << path_sum(cur[qx[i]]) << '\n';
        }
    }
    return 0;
}
