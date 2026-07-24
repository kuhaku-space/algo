#pragma once
#include <algorithm>
#include <iterator>
#include <vector>

/// @brief 座標圧縮
/// @tparam T 座標の型
/// @complexity 型宣言に実行時計算量はない
template <class T>
struct coordinate_compression {
    /// @brief 空の座標圧縮器を構築する
    /// @complexity $O(1)$
    coordinate_compression() = default;

    /// @brief 与えた列から座標圧縮器を構築する
    /// @param _data 圧縮対象の列
    /// @complexity 要素数を $n$ として $O(n\log n)$
    coordinate_compression(const std::vector<T> &_data) : data(_data) { build(); }

    /// @brief 圧縮後の番号から元の値を返す
    /// @complexity $O(1)$
    const T &operator[](int i) const { return data[i]; }

    /// @brief 最小の登録値を返す
    /// @complexity $O(1)$
    T front() const { return data.front(); }

    /// @brief 最大の登録値を返す
    /// @complexity $O(1)$
    T back() const { return data.back(); }

    /// @brief build前の列へ値を追加する
    /// @complexity 償却 $O(1)$
    void add(T x) { data.emplace_back(x); }

    /// @brief 登録値をソートして重複を除く
    /// @complexity 登録数を $n$ として $O(n\log n)$
    void build() {
        std::sort(data.begin(), data.end());
        data.erase(std::unique(data.begin(), data.end()), data.end());
    }

    /// @brief 値が登録されているか返す
    /// @complexity $O(\log n)$
    bool exists(T x) const {
        auto it = std::lower_bound(data.begin(), data.end(), x);
        return it != data.end() && *it == x;
    }

    /// @brief 値以上となる最初の圧縮番号を返す
    /// @complexity $O(\log n)$
    int get(T x) const { return std::distance(data.begin(), std::lower_bound(data.begin(), data.end(), x)); }

    /// @brief 値以上となる最初の圧縮番号を返す
    /// @complexity $O(\log n)$
    int lower_bound(T x) const { return std::distance(data.begin(), std::lower_bound(data.begin(), data.end(), x)); }

    /// @brief 値より大きくなる最初の圧縮番号を返す
    /// @complexity $O(\log n)$
    int upper_bound(T x) const { return std::distance(data.begin(), std::upper_bound(data.begin(), data.end(), x)); }

    /// @brief 列の各値を圧縮番号へ変換する
    /// @complexity 入力長を $k$ として $O(k\log n)$
    std::vector<int> compress(const std::vector<T> &v) const {
        int n = v.size();
        std::vector<int> res(n);
        for (int i = 0; i < n; ++i) res[i] = get(v[i]);
        return res;
    }

    /// @brief 異なる登録値の個数を返す
    /// @complexity $O(1)$
    int size() const { return data.size(); }

  private:
    std::vector<T> data;
};

/// @brief 座標圧縮
/// @param v 圧縮対象の列
/// @return 各要素を昇順の圧縮番号へ変換した列
/// @complexity 要素数を $n$ として $O(n\log n)$
template <class T>
std::vector<int> compress(const std::vector<T> &v) {
    coordinate_compression cps(v);
    std::vector<int> res;
    res.reserve(std::size(v));
    for (auto &&x : v) res.emplace_back(cps.get(x));
    return res;
}
