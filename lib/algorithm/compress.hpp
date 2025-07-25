#pragma once
#include <algorithm>
#include <iterator>
#include <vector>

/// @brief 座標圧縮
template <class T>
struct coordinate_compression {
    coordinate_compression() = default;
    coordinate_compression(const std::vector<T> &_data) : data(_data) { build(); }

    const T &operator[](int i) const { return data[i]; }
    T front() const { return data.front(); }
    T back() const { return data.back(); }

    void add(T x) { data.emplace_back(x); }

    void build() {
        std::sort(data.begin(), data.end());
        data.erase(std::unique(data.begin(), data.end()), data.end());
    }

    bool exists(T x) const {
        auto it = std::lower_bound(data.begin(), data.end(), x);
        return it != data.end() && *it == x;
    }

    int get(T x) const { return std::distance(data.begin(), std::lower_bound(data.begin(), data.end(), x)); }
    int lower_bound(T x) const { return std::distance(data.begin(), std::lower_bound(data.begin(), data.end(), x)); }
    int upper_bound(T x) const { return std::distance(data.begin(), std::upper_bound(data.begin(), data.end(), x)); }

    std::vector<int> compress(const std::vector<T> &v) const {
        int n = v.size();
        std::vector<int> res(n);
        for (int i = 0; i < n; ++i) res[i] = get(v[i]);
        return res;
    }

    int size() const { return data.size(); }

  private:
    std::vector<T> data;
};

/// @brief 座標圧縮
template <class T>
std::vector<int> compress(const std::vector<T> &v) {
    coordinate_compression cps(v);
    std::vector<int> res;
    res.reserve(std::size(v));
    for (auto &&x : v) res.emplace_back(cps.get(x));
    return res;
}
