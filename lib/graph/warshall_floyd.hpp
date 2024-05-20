#pragma once
#include "graph/matrix_graph.hpp"
#include "template/template.hpp"

template <class T>
void warshall_floyd(matrix_graph<T> &g) {
    int n = g.size();
    for (int i = 0; i < n; ++i) g[i][i] = T();
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) { chmin(g[i][j], g[i][k] + g[k][j]); }
        }
    }
}
