#include "template/template.hpp"

template <class T>
struct range_set {
    range_set() = default;

    std::pair<T, T> get(T x) const {
        auto it = intervals.lower_bound(std::make_pair(x, x));
        if (it == std::end(intervals) || !contains(x, *it))
            return std::make_pair(inf, inf);
        return std::make_pair(it->second, it->first);
    }

    bool contains(T x) const {
        auto it = intervals.lower_bound(std::make_pair(x, x));
        return it != std::end(intervals) && contains(x, *it);
    }

    bool same(T x, T y) const {
        auto it = intervals.lower_bound(std::make_pair(x, x));
        return it != std::end(intervals) && contains(x, *it) && contains(y, *it);
    }

    std::pair<T, T> insert(T x, T y) {
        assert(x < y);
        auto it = intervals.lower_bound(std::make_pair(x, std::numeric_limits<T>::lowest()));
        while (it != std::end(intervals) && it->second <= y) {
            x = std::min(x, it->second);
            y = std::max(y, it->first);
            it = intervals.erase(it);
        }
        intervals.emplace(y, x);
        return std::make_pair(x, y);
    }

    std::pair<T, T> insert(T x) {
        return insert(x, x + 1);
    }

    void erase(T x, T y) {
        assert(x < y);
        auto it = intervals.lower_bound(std::make_pair(x, x));
        if (it == std::end(intervals))
            return;
        if (it->second != x) {
            T l = it->second, r = it->first;
            intervals.erase(it);
            intervals.emplace(x, l);
            intervals.emplace(r, x);
        }
        it = intervals.lower_bound(std::make_pair(x, x));
        while (it != std::end(intervals)) {
            if (y <= it->second)
                break;
            if (y < it->first) {
                T r = it->first;
                intervals.erase(it);
                intervals.emplace(r, y);
                break;
            }
            it = intervals.erase(it);
        }
    }

    void erase(T x) {
        erase(x, x + 1);
    }

  private:
    static constexpr T inf = std::numeric_limits<T>::max();
    std::set<std::pair<T, T>> intervals;

    static bool contains(T x, const std::pair<T, T> &p) {
        return p.second <= x && x < p.first;
    }
};
