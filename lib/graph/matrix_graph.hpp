#pragma once
#include "template/template.hpp"

/**
 * @brief 隣接行列
 *
 * @tparam T
 */
template <class T>
struct matrix_graph {
    matrix_graph(int v, T e = T()) : _size(v), m(v, std::vector<T>(v, e)) {}

    const auto &operator[](int i) const { return this->m[i]; }
    auto &operator[](int i) { return this->m[i]; }
    const auto begin() const { return this->m.begin(); }
    auto begin() { return this->m.begin(); }
    const auto end() const { return this->m.end(); }
    auto end() { return this->m.end(); }

    constexpr int size() const { return this->_size; }

    void add_edge(int a, int b, T d = T(1)) { this->m[a][b] = d; }
    void add_edges(int a, int b, T d = T(1)) { this->m[a][b] = this->m[b][a] = d; }

    void input_edge(int m, int base = 1) {
        for (int i = 0; i < m; ++i) {
            int from, to;
            T weight;
            std::cin >> from >> to >> weight;
            this->add_edge(from - base, to - base, weight);
        }
    }
    void input_edges(int m, int base = 1) {
        for (int i = 0; i < m; ++i) {
            int from, to;
            T weight;
            std::cin >> from >> to >> weight;
            this->add_edges(from - base, to - base, weight);
        }
    }

  private:
    int _size;
    std::vector<std::vector<T>> m;
};

template <>
struct matrix_graph<void> {
    matrix_graph(int v) : _size(v), m(v, std::vector<bool>(v)) {}

    const auto &operator[](int i) const { return this->m[i]; }
    auto &operator[](int i) { return this->m[i]; }
    const auto begin() const { return this->m.begin(); }
    auto begin() { return this->m.begin(); }
    const auto end() const { return this->m.end(); }
    auto end() { return this->m.end(); }

    constexpr int size() const { return this->_size; }

    void add_edge(int a, int b) { this->m[a][b] = true; }
    void add_edges(int a, int b) { this->m[a][b] = this->m[b][a] = true; }

    void input_edge(int m, int base = 1) {
        for (int i = 0; i < m; ++i) {
            int from, to;
            std::cin >> from >> to;
            this->add_edge(from - base, to - base);
        }
    }
    void input_edges(int m, int base = 1) {
        for (int i = 0; i < m; ++i) {
            int from, to;
            std::cin >> from >> to;
            this->add_edges(from - base, to - base);
        }
    }

    void complement() {
        for (int i = 0; i < this->_size; ++i) {
            for (int j = 0; j < this->_size; ++j) this->m[i][j] = !this->m[i][j];
        }
    }

  private:
    int _size;
    std::vector<std::vector<bool>> m;
};
