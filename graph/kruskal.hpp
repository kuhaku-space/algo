#include "_base.hpp"
#include "graph/graph.hpp"
#include "tree/union_find.hpp"

// 最小全域木
template <class T>
vector<Graph<T>::edge> kruskal(const Graph<T> &g) {
    using _edge = Graph<T>::edge;
    union_find uf();
    vector<_edge> res;
    vector<_edge> edge_list;
    for (auto &v : g.edges) {
        edge_list.emplace(edge_list.end(), v.begin(), v.end());
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
