#pragma once
#include <algorithm>
#include <cassert>
#include <iterator>
#include <utility>
#include <vector>

/// @brief 部分永続配列
/// @tparam T 要素型
/// @note 更新は最新時刻に対してのみ行えるが、参照は任意の過去時刻に対して行える。各要素が
///       (時刻, 値) の履歴を持つ fat node 方式で、更新のたびに履歴を 1 つ末尾に積む。
/// @note 時刻は更新のたびに 1 進む。`set(k, val, t)` を使うと外部の時刻（非減少）をそのまま
///       割り当てられ、同一時刻に複数要素を更新できる。
/// @complexity 構築は $O(n)$、更新は償却 $O(1)$、参照は該当要素の更新回数を $q$ として $O(\log q)$
template <class T>
struct PartiallyPersistentArray {
    /// @brief 空の配列を構築する
    /// @complexity $O(1)$
    PartiallyPersistentArray() : _now(0) {}

    /// @brief n 個の val を時刻 0 の状態として作る
    /// @complexity $O(n)$
    PartiallyPersistentArray(int n, T val = T()) : _now(0), _data(n, std::vector<std::pair<int, T>>(1, {0, val})) {}

    /// @brief 列 v を時刻 0 の状態として作る
    /// @complexity $O(n)$
    template <class U>
    PartiallyPersistentArray(const std::vector<U> &v) : _now(0), _data(v.size()) {
        for (int i = 0; i < (int)v.size(); ++i) _data[i].emplace_back(0, T(v[i]));
    }

    /// @brief 要素数を返す
    /// @complexity $O(1)$
    int size() const { return _data.size(); }

    /// @brief 現在時刻を返す
    /// @complexity $O(1)$
    int now() const { return _now; }

    /// @brief 現在時刻における k 番目の値を返す
    /// @complexity $O(\log q)$
    T operator[](int k) const { return get(k, _now); }
    /// @brief `operator[](k)` の別名
    /// @complexity $O(\log q)$
    T at(int k) const { return get(k, _now); }
    /// @brief `operator[](k)` の別名
    /// @complexity $O(\log q)$
    T get(int k) const { return get(k, _now); }

    /// @brief 時刻 t における k 番目の値を返す。t が現在時刻を超える場合は最新の値を返す
    /// @complexity $O(\log q)$
    T get(int k, int t) const {
        assert(0 <= k && k < size());
        assert(0 <= t);
        const auto &history = _data[k];
        return std::prev(std::ranges::upper_bound(history, t, {}, &std::pair<int, T>::first))->second;
    }
    /// @brief `get(k, t)` の別名
    /// @complexity $O(\log q)$
    T at(int k, int t) const { return get(k, t); }

    /// @brief 時刻を 1 進めて k 番目を val に変更する
    /// @return 更新後の時刻
    /// @complexity 償却 $O(1)$
    int set(int k, T val) {
        set(k, val, _now + 1);
        return _now;
    }

    /// @brief 現在時刻以上の時刻 t で k 番目を val に変更し、現在時刻を t にする
    /// @note 同一時刻に同じ要素を複数回更新した場合は最後の値が採用される
    /// @complexity 償却 $O(1)$
    void set(int k, T val, int t) {
        assert(0 <= k && k < size());
        assert(_now <= t);
        _now = t;
        _data[k].emplace_back(t, val);
    }

    /// @brief 現在時刻における配列全体を返す
    /// @complexity $O(n\log q)$
    std::vector<T> to_vector() const { return to_vector(_now); }

    /// @brief 時刻 t における配列全体を返す
    /// @complexity $O(n\log q)$
    std::vector<T> to_vector(int t) const {
        std::vector<T> res(size());
        for (int i = 0; i < size(); ++i) res[i] = get(i, t);
        return res;
    }

  private:
    int _now;
    std::vector<std::vector<std::pair<int, T>>> _data;
};
