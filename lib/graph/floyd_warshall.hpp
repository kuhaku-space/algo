#pragma once
#include <algorithm>
#include "graph/matrix_graph.hpp"

/// @brief ワーシャルフロイド法
template <class T>
void floyd_warshall(matrix_graph<T> &g) {
    int n = g.size();
    for (int i = 0; i < n; ++i) g[i][i] = T();
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) { g[i][j] = std::min(g[i][j], g[i][k] + g[k][j]); }
        }
    }
}
