#include "template/template.hpp"

template <class T>
struct Graph {
    struct edge {
        std::int64_t from, to;
        T dist;

        bool operator<(const edge &rhs) const { return dist < rhs.dist; }
        bool operator>(const edge &rhs) const { return dist > rhs.dist; }
        edge &operator+=(const edge &rhs) {
            to = rhs.to, dist += rhs.dist;
            return *this;
        }
        edge operator+(const edge &rhs) { return edge(*this) += rhs; }
    };

    std::int64_t V;
    std::vector<T> dist;
    std::vector<std::vector<edge>> edges;

    Graph(std::int64_t v) : V(v), edges(v * 5), dist(v, numeric_limits<T>::max()) {
        for (std::int64_t i = 2; i < v * 2; ++i) {
            edges.push_back(edge{v + i >> 1, v + i, 0});
            edges.push_back(edge{v * 3 + i, v * 3 + i >> 1, 0});
        }
        for (std::int64_t i = 0; i < v; ++i) {
            edges.push_back(edge{v * 2 + i, i, 0});
            edges.push_back(edge{v * 4 + i, i, 0});
        }
    }

    void add_edge(std::int64_t a1, std::int64_t b1, std::int64_t a2, std::int64_t b2, T d = 1,
                  bool is_dual = false) {
        if (is_dual) add_edge(a2, b2, a1, b1, d, !is_dual);
        std::int64_t n = edges.size();
        edges.resize(n + 2);
        edges[n].emplace_back(edge{n, n + 1, d});
        for (a1 += V, b1 += V; a1 < b1; a1 >>= 1, b1 >>= 1) {
            if (a1 & 1) edges[V * 3 + a1].emplace_back(edge{V * 3 + a1, n, 0}), ++a1;
            if (b1 & 1) --b1, edges[V * 3 + b1].emplace_back(edge{V * 3 + b1, n, 0});
        }
        for (a2 += V, b2 += V; a2 < b2; a2 >>= 1, b2 >>= 1) {
            if (a2 & 1) edges[n + 1].emplace_back(edge{n + 1, V + a2, 0}), ++a2;
            if (b2 & 1) --b2, edges[n + 1].emplace_back(edge{n + 1, V + b2, 0});
        }
    }
};
