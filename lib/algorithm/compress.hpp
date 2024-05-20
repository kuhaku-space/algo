#pragma once
#include <algorithm>
#include <iterator>
#include <vector>

/**
 * @brief 座標圧縮
 *
 * @tparam T 要素の型
 */
template <class T>
struct coordinate_compression {
    coordinate_compression() = default;
    coordinate_compression(const std::vector<T> &_data) : data(_data) { build(); }

    const T &operator[](int i) const { return data[i]; }
    T &operator[](int i) { return data[i]; }

    void add(T x) { data.emplace_back(x); }

    void build() {
        std::sort(std::begin(data), std::end(data));
        data.erase(std::unique(std::begin(data), std::end(data)), std::end(data));
    }

    bool exists(T x) const {
        auto it = std::lower_bound(std::begin(data), std::end(data), x);
        return it != std::end(data) && *it == x;
    }

    int get(T x) const {
        auto it = std::lower_bound(std::begin(data), std::end(data), x);
        return std::distance(std::begin(data), it);
    }

    int size() const { return std::size(data); }

  private:
    std::vector<T> data;
};

/**
 * @brief 座標圧縮
 *
 * @tparam T 要素の型
 * @param v 配列
 * @return std::vector<T>
 */
template <class T>
std::vector<T> compress(const std::vector<T> &v) {
    coordinate_compression cps(v);
    std::vector<T> res;
    res.reserve(std::size(v));
    for (auto &&x : v) res.emplace_back(cps.get(x));
    return res;
}
