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

    void add(T x) { data.emplace_back(x); }

    void build() {
        std::sort(data.begin(), data.end());
        data.erase(std::unique(data.begin(), data.end()), data.end());
    }

    bool exists(T x) const {
        auto it = std::lower_bound(data.begin(), data.end(), x);
        return it != data.end() && *it == x;
    }

    int get(T x) const {
        auto it = std::lower_bound(data.begin(), data.end(), x);
        return std::distance(data.begin(), it);
    }

    int size() const { return data.size(); }

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
std::vector<int> compress(const std::vector<T> &v) {
    coordinate_compression cps(v);
    std::vector<int> res;
    res.reserve(std::size(v));
    for (auto &&x : v) res.emplace_back(cps.get(x));
    return res;
}
