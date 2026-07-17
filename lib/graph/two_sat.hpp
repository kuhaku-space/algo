#pragma once
#include <vector>
#include "graph/scc.hpp"
#include "internal/internal_csr.hpp"

/// @brief 2-SAT
struct two_sat {
    two_sat(int n) : _size(n) {}

    void add(int i, bool f, int j, bool g) {
        i <<= 1, j <<= 1;
        edges.emplace_back(i + (f ? 0 : 1), j + (g ? 1 : 0));
        edges.emplace_back(j + (g ? 0 : 1), i + (f ? 1 : 0));
    }

    std::vector<int> solve() {
        internal::Csr<int> G(_size * 2, edges);
        auto res = scc(G);
        return res;
    }

    bool is_satisfy(const std::vector<int> &v) {
        for (int i = 0; i < _size; ++i) {
            if (v[i * 2] == v[i * 2 + 1]) return false;
        }
        return true;
    }

    std::vector<bool> build(const std::vector<int> &v) {
        std::vector<bool> res(_size);
        for (int i = 0; i < _size; ++i) res[i] = v[i * 2] < v[i * 2 + 1];
        return res;
    }

  private:
    int _size;
    std::vector<std::pair<int, int>> edges;
};
