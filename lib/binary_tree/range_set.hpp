#pragma once
#include <algorithm>
#include <cassert>
#include <limits>
#include <set>
#include <utility>

/// @brief 区間をsetで管理するテク
template <class T>
struct range_set {
    range_set() : intervals(), len() {}

    std::set<std::pair<T, T>>::const_iterator begin() const { return intervals.begin(); }
    std::set<std::pair<T, T>>::const_iterator end() const { return intervals.end(); }

    int size() const { return intervals.size(); }
    T length() const { return len; }

    std::pair<T, T> get(T x) const {
        auto it = intervals.lower_bound(std::make_pair(x, x));
        if (it == intervals.end() || !contains(x, *it)) return std::make_pair(inf, inf);
        return std::make_pair(it->second, it->first);
    }

    bool contains(T x) const {
        auto it = intervals.lower_bound(std::make_pair(x, x));
        return it != intervals.end() && contains(x, *it);
    }

    bool same(T x, T y) const {
        auto it = intervals.lower_bound(std::make_pair(x, x));
        return it != intervals.end() && contains(x, *it) && contains(y, *it);
    }

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

    std::pair<T, T> insert(T x) { return insert(x, x + 1); }

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

    void erase(T x) { erase(x, x + 1); }

  private:
    static constexpr T inf = std::numeric_limits<T>::max();
    std::set<std::pair<T, T>> intervals;
    T len;

    static bool contains(T x, const std::pair<T, T> &p) { return p.second <= x && x < p.first; }
};
