#pragma once
#include <iostream>
#include <utility>
#include <vector>

namespace internal {

struct graph_csr {
  private:
    struct edge_list {
        using const_iterator = std::vector<int>::const_iterator;

        edge_list(const graph_csr &g, int v) : g(g), v(v) {}

        const_iterator begin() const { return std::next(g.elist.begin(), g.start[v]); }
        const_iterator end() const { return std::next(g.elist.begin(), g.start[v + 1]); }

      private:
        const graph_csr &g;
        int v;
    };

  public:
    graph_csr(int n) : _size(n), edges(), start(n + 1) {}

    edge_list operator[](int i) const { return edge_list(*this, i); }

    constexpr int size() const { return _size; }

    void build() {
        for (auto [u, v] : edges) ++start[u + 1];
        for (int i = 0; i < _size; ++i) start[i + 1] += start[i];
        auto counter = start;
        elist = std::vector<int>(edges.size());
        for (auto [u, v] : edges) elist[counter[u]++] = v;
    }

    void add_edge(int u, int v) { edges.emplace_back(u, v); }

    void add_edges(int u, int v) {
        edges.emplace_back(u, v);
        edges.emplace_back(v, u);
    }

    void input_edge(int m, int base = 1) {
        for (int i = 0; i < m; ++i) {
            int from, to;
            std::cin >> from >> to;
            add_edge(from - base, to - base);
        }
        build();
    }

    void input_edges(int m, int base = 1) {
        for (int i = 0; i < m; ++i) {
            int from, to;
            std::cin >> from >> to;
            add_edges(from - base, to - base);
        }
        build();
    }

    int _size;
    std::vector<std::pair<int, int>> edges;
    std::vector<int> elist;
    std::vector<int> start;
};

template <class E>
struct csr {
    std::vector<int> start;
    std::vector<E> elist;
    explicit csr(int n, const std::vector<std::pair<int, E>> &edges) : start(n + 1), elist(edges.size()) {
        for (auto e : edges) ++start[e.first + 1];
        for (int i = 1; i <= n; ++i) start[i] += start[i - 1];
        auto counter = start;
        for (auto e : edges) elist[counter[e.first]++] = e.second;
    }
};

}  // namespace internal
