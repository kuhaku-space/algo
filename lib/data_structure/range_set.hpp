#pragma once
#include <algorithm>
#include <cassert>
#include <limits>
#include <set>
#include <utility>

/// @brief 区間をsetで管理するテク
template <class T>
struct range_set {
    /// @brief 空の区間集合を構築する
    /// @complexity $O(1)$
    range_set() : intervals(), len() {}

    /// @brief 区間集合の先頭イテレータを返す
    /// @complexity $O(1)$
    std::set<std::pair<T, T>>::const_iterator begin() const { return intervals.begin(); }

    /// @brief 区間集合の終端イテレータを返す
    /// @complexity $O(1)$
    std::set<std::pair<T, T>>::const_iterator end() const { return intervals.end(); }

    /// @brief 互いに素な区間の個数を返す
    /// @complexity $O(1)$
    int size() const { return intervals.size(); }

    /// @brief 区間集合が覆う長さの総和を返す
    /// @complexity $O(1)$
    T length() const { return len; }

    /// @brief xを含む半開区間を返す
    /// @complexity 区間数を $q$ として $O(\log q)$
    std::pair<T, T> get(T x) const {
        auto it = intervals.lower_bound(std::make_pair(x, x));
        if (it == intervals.end() || !contains(x, *it)) return std::make_pair(inf, inf);
        return std::make_pair(it->second, it->first);
    }

    /// @brief xが区間集合に含まれるか返す
    /// @complexity $O(\log q)$
    bool contains(T x) const {
        auto it = intervals.lower_bound(std::make_pair(x, x));
        return it != intervals.end() && contains(x, *it);
    }

    /// @brief xとyが同じ管理区間に含まれるか返す
    /// @complexity $O(\log q)$
    bool same(T x, T y) const {
        auto it = intervals.lower_bound(std::make_pair(x, x));
        return it != intervals.end() && contains(x, *it) && contains(y, *it);
    }

    /// @brief 半開区間を追加して連結する区間を併合する
    /// @complexity 併合する区間数を $k$ として $O((k+1)\log q)$
    std::pair<T, T> insert(T x, T y) {
        assert(x <= y);
        if (x == y) return std::make_pair(x, y);
        auto it = intervals.lower_bound(std::make_pair(x, std::numeric_limits<T>::lowest()));
        while (it != intervals.end() && it->second <= y) {
            len -= it->first - it->second;
            x = std::min(x, it->second);
            y = std::max(y, it->first);
            it = intervals.erase(it);
        }
        len += y - x;
        intervals.emplace(y, x);
        return std::make_pair(x, y);
    }

    /// @brief 1点に対応する単位区間を追加する
    /// @complexity $O(\log q)$
    std::pair<T, T> insert(T x) { return insert(x, x + 1); }

    /// @brief 半開区間を削除する
    /// @complexity 削除する区間数を $k$ として $O((k+1)\log q)$
    void erase(T x, T y) {
        assert(x <= y);
        if (x == y) return;
        auto it = intervals.lower_bound(std::make_pair(x, x));
        if (it == intervals.end()) return;
        if (contains(x, *it)) {
            T l = it->second, r = it->first;
            intervals.erase(it);
            if (l < x) intervals.emplace(x, l);
            if (x < r) intervals.emplace(r, x);
        }
        it = intervals.lower_bound(std::make_pair(x, x));
        while (it != intervals.end()) {
            if (y <= it->second) break;
            if (y < it->first) {
                T r = it->first;
                len -= y - it->second;
                intervals.erase(it);
                intervals.emplace(r, y);
                break;
            }
            len -= it->first - it->second;
            it = intervals.erase(it);
        }
    }

    /// @brief 1点に対応する単位区間を削除する
    /// @complexity $O(\log q)$
    void erase(T x) { erase(x, x + 1); }

  private:
    static constexpr T inf = std::numeric_limits<T>::max();
    std::set<std::pair<T, T>> intervals;
    T len;

    static bool contains(T x, const std::pair<T, T> &p) { return p.second <= x && x < p.first; }
};
