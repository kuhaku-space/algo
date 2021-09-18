#include "_base.hpp"

template <class T>
struct Graph {
    int V;
    vector<vector<T>> m;

    Graph(int v, T _e = T()) : V(v) {
        m = vector<vector<T>>(V, vector<T>(V, _e));
    }

    const auto &operator[](int i) const { return m[i]; }
    auto &operator[](int i) { return m[i]; }
    const auto begin() const { return m.begin(); }
    auto begin() { return m.begin(); }
    const auto end() const { return m.end(); }
    auto end() { return m.end(); }

    int size() const { return V; }

    void add_edge(int a, int b, T d = T(1)) { m[a][b] = d; }
    void add_edges(int a, int b, T d = T(1)) {
        m[a][b] = d;
        m[b][a] = d;
    }

    void complement() {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) m[i][j] = !m[i][j];
        }
    }
};
