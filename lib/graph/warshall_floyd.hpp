#include "template/template.hpp"
#include "graph/graph_matrix.hpp"

template <class T>
void warshall_floyd(Graph<T> &g) {
    int n = g.size();
    for (int i = 0; i < n; ++i) g[i][i] = 0;
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                chmin(g[i][j], g[i][k] + g[k][j]);
            }
        }
    }
}
