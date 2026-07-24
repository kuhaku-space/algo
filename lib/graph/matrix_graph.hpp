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
/// @complexity 構築は $O(V^2)$、辺追加・参照は $O(1)$
template <class T>
struct matrix_graph {
    /// @brief 辺重みの型
    /// @complexity 型エイリアスで実行時計算量はない
    using value_type = T;

    /// @brief v頂点の全成分をeで初期化する
    /// @complexity $O(V^2)$
    explicit matrix_graph(int v, T e = T()) : _size(v), mat(v, std::vector<T>(v, e)) {}

    /// @brief 頂点iからの行を返す
    /// @complexity $O(1)$
    const auto &operator[](int i) const {
        assert(0 <= i && i < _size);
        return mat[i];
    }

    /// @brief 頂点iからの行を変更可能な参照で返す
    /// @complexity $O(1)$
    auto &operator[](int i) {
        assert(0 <= i && i < _size);
        return mat[i];
    }

    /// @brief 行列の先頭iteratorを返す
    /// @complexity $O(1)$
    auto begin() const { return mat.begin(); }

    /// @brief 行列の先頭iteratorを返す
    /// @complexity $O(1)$
    auto begin() { return mat.begin(); }

    /// @brief 行列の終端iteratorを返す
    /// @complexity $O(1)$
    auto end() const { return mat.end(); }

    /// @brief 行列の終端iteratorを返す
    /// @complexity $O(1)$
    auto end() { return mat.end(); }

    /// @brief 頂点数を返す
    /// @complexity $O(1)$
    constexpr int size() const { return _size; }

    /// @brief 有向辺 a→b を重み d で張る（既存の重みとは最小値でマージ）。
    /// @complexity $O(1)$
    void add_edge(int a, int b, T d = T(1)) {
        assert(0 <= a && a < _size);
        assert(0 <= b && b < _size);
        mat[a][b] = std::min<T>(mat[a][b], d);
    }
    /// @brief 無向辺 a-b を重み d で張る（既存の重みとは最小値でマージ）。
    /// @complexity $O(1)$
    void add_edges(int a, int b, T d = T(1)) {
        assert(0 <= a && a < _size);
        assert(0 <= b && b < _size);
        mat[a][b] = mat[b][a] = std::min<T>(mat[a][b], d);
    }

    /// @brief 標準入力からm本の有向辺を追加する
    /// @complexity $O(m)$
    void input_edge(int m, int origin = 1) {
        for (int i = 0; i < m; ++i) {
            int from, to;
            T weight;
            std::cin >> from >> to >> weight;
            add_edge(from - origin, to - origin, weight);
        }
    }

    /// @brief 標準入力からm本の無向辺を追加する
    /// @complexity $O(m)$
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

/// @brief 重みなし隣接行列
/// @complexity 構築は $O(V^2)$、辺追加・参照は $O(1)$
template <>
struct matrix_graph<void> {
    /// @brief 隣接状態の型
    /// @complexity 型エイリアスで実行時計算量はない
    using value_type = bool;

    /// @brief v頂点の空グラフを構築する
    /// @complexity $O(V^2)$
    explicit matrix_graph(int v) : _size(v), mat(v, std::vector<bool>(v)) {}

    /// @brief 頂点iからの行を返す
    /// @complexity $O(1)$
    const auto &operator[](int i) const {
        assert(0 <= i && i < _size);
        return mat[i];
    }

    /// @brief 頂点iからの行を変更可能な参照で返す
    /// @complexity $O(1)$
    auto &operator[](int i) {
        assert(0 <= i && i < _size);
        return mat[i];
    }

    /// @brief 行列の先頭iteratorを返す
    /// @complexity $O(1)$
    auto begin() const { return mat.begin(); }

    /// @brief 行列の先頭iteratorを返す
    /// @complexity $O(1)$
    auto begin() { return mat.begin(); }

    /// @brief 行列の終端iteratorを返す
    /// @complexity $O(1)$
    auto end() const { return mat.end(); }

    /// @brief 行列の終端iteratorを返す
    /// @complexity $O(1)$
    auto end() { return mat.end(); }

    /// @brief 頂点数を返す
    /// @complexity $O(1)$
    constexpr int size() const { return _size; }

    /// @brief 有向辺 a→b を張る。
    /// @complexity $O(1)$
    void add_edge(int a, int b) {
        assert(0 <= a && a < _size);
        assert(0 <= b && b < _size);
        mat[a][b] = true;
    }
    /// @brief 無向辺 a-b を張る。
    /// @complexity $O(1)$
    void add_edges(int a, int b) {
        assert(0 <= a && a < _size);
        assert(0 <= b && b < _size);
        mat[a][b] = mat[b][a] = true;
    }

    /// @brief 標準入力からm本の有向辺を追加する
    /// @complexity $O(m)$
    void input_edge(int m, int origin = 1) {
        for (int i = 0; i < m; ++i) {
            int from, to;
            std::cin >> from >> to;
            add_edge(from - origin, to - origin);
        }
    }

    /// @brief 標準入力からm本の無向辺を追加する
    /// @complexity $O(m)$
    void input_edges(int m, int origin = 1) {
        for (int i = 0; i < m; ++i) {
            int from, to;
            std::cin >> from >> to;
            add_edges(from - origin, to - origin);
        }
    }

    /// @brief 補グラフに変換する（自己ループ含む全成分を反転）。
    /// @complexity $O(V^2)$
    void complement() {
        for (int i = 0; i < _size; ++i) {
            for (int j = 0; j < _size; ++j) mat[i][j] = !mat[i][j];
        }
    }

  private:
    int _size;
    std::vector<std::vector<bool>> mat;
};
