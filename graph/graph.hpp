#include "_base.hpp"

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

    int V;
    vector<vector<edge>> edges;

    Graph(int64_t v) : V(v) { edges = vector<vector<edge>>(V); }

    int size() const { return V; }

    void add_edge(int64_t a, int64_t b, T d = T(1)) {
        edges[a].push_back(edge{a, b, d});
    }
    void add_edges(int64_t a, int64_t b, T d = T(1)) {
        edges[a].push_back(edge{a, b, d});
        edges[b].push_back(edge{b, a, d});
    }
};
