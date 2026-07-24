#pragma once
#include <vector>
#include "graph/scc.hpp"
#include "internal/internal_csr.hpp"

/// @brief 2-SAT
/// @complexity 変数数を $V$、節数を $C$ として構築 $O(V)$、求解 $O(V+C)$
struct two_sat {
    /// @brief n変数の2-SATを構築する
    /// @complexity $O(V)$
    two_sat(int n) : _size(n) {}

    /// @brief 節(iがf) OR (jがg)を追加する
    /// @complexity 償却 $O(1)$
    void add(int i, bool f, int j, bool g) {
        i <<= 1, j <<= 1;
        edges.emplace_back(i + (f ? 0 : 1), j + (g ? 1 : 0));
        edges.emplace_back(j + (g ? 0 : 1), i + (f ? 1 : 0));
    }

    /// @brief 含意グラフの強連結成分番号を返す
    /// @complexity $O(V+C)$
    std::vector<int> solve() {
        internal::Csr<int> G(_size * 2, edges);
        auto res = scc(G);
        return res;
    }

    /// @brief solveが返した成分番号が充足可能か確認する
    /// @complexity $O(V)$
    bool is_satisfy(const std::vector<int> &v) {
        for (int i = 0; i < _size; ++i) {
            if (v[i * 2] == v[i * 2 + 1]) return false;
        }
        return true;
    }

    /// @brief 成分番号から各変数の真偽値を構築する
    /// @complexity $O(V)$
    std::vector<bool> build(const std::vector<int> &v) {
        std::vector<bool> res(_size);
        for (int i = 0; i < _size; ++i) res[i] = v[i * 2] < v[i * 2 + 1];
        return res;
    }

  private:
    int _size;
    std::vector<std::pair<int, int>> edges;
};
