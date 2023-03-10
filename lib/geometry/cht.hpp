#include "template/template.hpp"

/**
 * @brief Convex Hull Trick
 *
 * Usage:
 * CHT cht(ll(1e13), [](ll l, ll r) { return l >= r; });
 *
 * @tparam T 要素の型
 * @tparam Comp 比較関数
 */
template <class T, class Comp>
struct CHT {
    CHT(T _e, Comp _comp) : comp(_comp) { lines.emplace_back(0, _e); };

    void add(T a, T b) {
        std::pair<T, T> line(a, b);
        while (lines.size() >= 2 && check(*(lines.end() - 2), lines.back(), line)) lines.pop_back();
        lines.emplace_back(line);
    }

    T f(int i, T x) { return lines[i].first * x + lines[i].second; }
    T f(std::pair<T, T> line, T x) { return line.first * x + line.second; }

    T get(T x) {
        int low = -1, high = lines.size() - 1;
        while (high - low > 1) {
            int mid = (high + low) / 2;
            if (comp(f(mid, x), f(mid + 1, x))) low = mid;
            else high = mid;
        }
        return f(high, x);
    }

  private:
    std::vector<std::pair<T, T>> lines;
    Comp comp;

    bool check(std::pair<T, T> l1, std::pair<T, T> l2, std::pair<T, T> l3) {
        if (l1 < l3) swap(l1, l3);
        return (l3.second - l2.second) * (l2.first - l1.first) >=
               (l2.second - l1.second) * (l3.first - l2.first);
    }
};
