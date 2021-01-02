#include "_base.hpp"

template<class T>
struct Graph {
    int64_t V;
    vector<vector<T>> dist;

    Graph (int64_t _V) : V(_V) {
        dist.resize(V);
        for (int64_t i = 0; i < V; ++i) {
            dist[i].resize(V, LINF);
        }
    }

    void add_edge(int64_t a, int64_t b, int64_t d) {
        dist[a][b] = d;
        dist[b][a] = d;
    }

    void warshall_floyd() {
        for (int64_t i = 0; i < V; ++i) {
            dist[i][i] = 0;
        }
        for (int64_t k = 0; k < V; ++k) {
            for (int64_t i = 0; i < V; ++i) {
                for (int64_t j = 0; j < V; ++j) {
                    chmin(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
};
