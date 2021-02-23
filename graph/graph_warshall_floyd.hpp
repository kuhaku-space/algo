#include "_base.hpp"

template <class T>
struct Graph {
    int V;
    vector<vector<T>> dist;

    Graph(int _V) : V(_V) { dist = vector<vector<T>>(V, vector<T>(V)); }

    const vector<T> &operator[](int i) const { return dist[i]; }
    vector<T> &operator[](int i) { return dist[i]; }

    void add_edge(int a, int b, T d) {
        dist[a][b] = d;
        dist[b][a] = d;
    }

    void warshall_floyd() {
        for (int i = 0; i < V; ++i) dist[i][i] = 0;
        for (int k = 0; k < V; ++k) {
            for (int i = 0; i < V; ++i) {
                for (int j = 0; j < V; ++j) {
                    chmin(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
};
