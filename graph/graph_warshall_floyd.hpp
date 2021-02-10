#include "_base.hpp"

template <class T>
struct Graph {
    int64_t V;
    vector<vector<T>> dist;

    Graph(int64_t _V) : V(_V) {
        dist = vector<vector<T>>(V, vector<int64_t>(V));
    }

    const vector<T> &operator[](int64_t i) const { return dist[i]; }
    vector<T> &operator[](int64_t i) { return dist[i]; }

    void add_edge(int64_t a, int64_t b, T d) {
        dist[a][b] = d;
        dist[b][a] = d;
    }

    void warshall_floyd() {
        for (int64_t i = 0; i < V; ++i) dist[i][i] = 0;
        for (int64_t k = 0; k < V; ++k) {
            for (int64_t i = 0; i < V; ++i) {
                for (int64_t j = 0; j < V; ++j) {
                    chmin(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
};
