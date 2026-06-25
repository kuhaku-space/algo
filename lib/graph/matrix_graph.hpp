#pragma once
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

/// @brief 隣接行列
/// @tparam T 辺の重みの型。`void` を指定すると重みなしグラフ（隣接の有無を bool で持つ）になる。
/// @note 距離行列としての利用を前提に、`add_edge` / `add_edges` は同一頂点対の重みを
///       最小値でマージする（多重辺は最小重みを残す）。「辺なし」を表す番兵（INF など）で
///       初期化しておくこと。`mat[a][b]` を直接代入すれば任意の値を上書きできる。
template <class T>
struct matrix_graph {
    using value_type = T;

    explicit matrix_graph(int v, T e = T()) : _size(v), mat(v, std::vector<T>(v, e)) {}

    const auto &operator[](int i) const {
        assert(0 <= i && i < _size);
        return mat[i];
    }
    auto &operator[](int i) {
        assert(0 <= i && i < _size);
        return mat[i];
    }
    auto begin() const { return mat.begin(); }
    auto begin() { return mat.begin(); }
    auto end() const { return mat.end(); }
    auto end() { return mat.end(); }

    constexpr int size() const { return _size; }

    /// @brief 有向辺 a→b を重み d で張る（既存の重みとは最小値でマージ）。
    void add_edge(int a, int b, T d = T(1)) {
        assert(0 <= a && a < _size);
        assert(0 <= b && b < _size);
        mat[a][b] = std::min<T>(mat[a][b], d);
    }
    /// @brief 無向辺 a-b を重み d で張る（既存の重みとは最小値でマージ）。
    void add_edges(int a, int b, T d = T(1)) {
        assert(0 <= a && a < _size);
        assert(0 <= b && b < _size);
        mat[a][b] = mat[b][a] = std::min<T>(mat[a][b], d);
    }

    void input_edge(int m, int origin = 1) {
        for (int i = 0; i < m; ++i) {
            int from, to;
            T weight;
            std::cin >> from >> to >> weight;
            add_edge(from - origin, to - origin, weight);
        }
    }
    void input_edges(int m, int origin = 1) {
        for (int i = 0; i < m; ++i) {
            int from, to;
            T weight;
            std::cin >> from >> to >> weight;
            add_edges(from - origin, to - origin, weight);
        }
    }

  private:
    int _size;
    std::vector<std::vector<T>> mat;
};

template <>
struct matrix_graph<void> {
    using value_type = bool;

    explicit matrix_graph(int v) : _size(v), mat(v, std::vector<bool>(v)) {}

    const auto &operator[](int i) const {
        assert(0 <= i && i < _size);
        return mat[i];
    }
    auto &operator[](int i) {
        assert(0 <= i && i < _size);
        return mat[i];
    }
    auto begin() const { return mat.begin(); }
    auto begin() { return mat.begin(); }
    auto end() const { return mat.end(); }
    auto end() { return mat.end(); }

    constexpr int size() const { return _size; }

    /// @brief 有向辺 a→b を張る。
    void add_edge(int a, int b) {
        assert(0 <= a && a < _size);
        assert(0 <= b && b < _size);
        mat[a][b] = true;
    }
    /// @brief 無向辺 a-b を張る。
    void add_edges(int a, int b) {
        assert(0 <= a && a < _size);
        assert(0 <= b && b < _size);
        mat[a][b] = mat[b][a] = true;
    }

    void input_edge(int m, int origin = 1) {
        for (int i = 0; i < m; ++i) {
            int from, to;
            std::cin >> from >> to;
            add_edge(from - origin, to - origin);
        }
    }
    void input_edges(int m, int origin = 1) {
        for (int i = 0; i < m; ++i) {
            int from, to;
            std::cin >> from >> to;
            add_edges(from - origin, to - origin);
        }
    }

    /// @brief 補グラフに変換する（自己ループ含む全成分を反転）。
    void complement() {
        for (int i = 0; i < _size; ++i) {
            for (int j = 0; j < _size; ++j) mat[i][j] = !mat[i][j];
        }
    }

  private:
    int _size;
    std::vector<std::vector<bool>> mat;
};
