// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/2020
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include "data_structure/fenwick_tree.hpp"
#include "graph/graph.hpp"
#include "string/trie.hpp"
#include "tree/euler_tour.hpp"

int main() {
    int n;
    std::cin >> n;

    LowerTrie trie;
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
    list_graph<int> g(m);
    for (int v = 0; v < m; ++v) {
        const auto node = trie.get_node(v);
        for (int c = 0; c < 26; ++c) {
            int u = node.next_node[c];
            if (u != -1) g.add_edge(v, u);
        }
    }
    euler_tour et(g, 0);

    FenwickTree<std::int64_t> bit(m);
    auto mark = [&](int v) {
        et.query(v, [&](int l, int r) {
            bit.add(l, 1);
            if (r < m) bit.add(r, -1);
        });
    };
    auto query = [&](int v) { return bit.sum(0, et.left(v) + 1); };

    std::vector<int> cur(n);
    for (int i = 0; i < n; ++i) {
        for (int v : init_path[i]) mark(v);
        cur[i] = init_path[i].empty() ? 0 : init_path[i].back();
    }

    for (int i = 0; i < q; ++i) {
        if (qtype[i] == 1) {
            mark(qadd[i]);
            cur[qx[i]] = qadd[i];
        } else {
            std::cout << query(cur[qx[i]]) << '\n';
        }
    }
    return 0;
}
