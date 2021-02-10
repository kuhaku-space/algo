#include "_base.hpp"
#include "tree/union_find.hpp"

template <class T>
struct Graph {
    struct edge {
        int64_t from, to;
        T dist;

        bool operator<(const edge &rhs) const { return dist < rhs.dist; }

        bool operator>(const edge &rhs) const { return dist > rhs.dist; }

        edge &operator+=(const edge &rhs) {
            to = rhs.to;
            dist += rhs.dist;
            return *this;
        }
        edge operator+(const edge &rhs) { return edge(*this) += rhs; }
    };

    int64_t V;
    vector<T> dist;
    vector<vector<edge>> edges;

    Graph(int64_t v) : V(v) {
        edges = vector<vector<edge>>(V);
        dist = vector<T>(V, numeric_limits<T>::max());
    }

    void add_edge(int64_t a, int64_t b, T d = T(1)) {
        edges[a].push_back(edge{a, b, d});
    }
    void add_edge(int64_t a, int64_t b, T d = T(1)) {
        edges[a].push_back(edge{a, b, d});
        edges[b].push_back(edge{b, a, d});
    }

    // 最小全域木
    T kruskal() {
        union_find uf(V);
        T res = T();
        vector<edge> edge_list;
        for (auto v : edges) {
            for (auto e : v) edge_list.push_back(e);
        }
        sort(edge_list.begin(), edge_list.end());
        for (edge e : edge_list) {
            if (!uf.is_same(e.from, e.to)) {
                uf.unite(e.from, e.to);
                res += e.dist;
            }
        }
        return res;
    }
};
