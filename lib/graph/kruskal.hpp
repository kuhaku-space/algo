#include "template/template.hpp"
#include "graph/graph.hpp"
#include "tree/union_find.hpp"

// verify : https://onlinejudge.u-aizu.ac.jp/problems/GRL_2_A 21/02/24

// 最小全域木
template <class T>
vector<typename Graph<T>::edge> kruskal(const Graph<T> &g) {
    using _edge = typename Graph<T>::edge;
    union_find uf(g.size());
    vector<_edge> res;
    vector<_edge> edge_list;
    for (auto &v : g) {
        for (auto &e : v) edge_list.emplace_back(e);
    }
    sort(edge_list.begin(), edge_list.end());
    for (auto &e : edge_list) {
        if (!uf.is_same(e.from, e.to)) {
            uf.unite(e.from, e.to);
            res.emplace_back(e);
        }
    }
    return res;
}
