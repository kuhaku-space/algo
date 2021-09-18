#include "lib/template/template.hpp"

/*
 * Usage:
 * CHT cht(ll(1e13), [](ll l, ll r) { return l >= r; });
 */
template <class T, class F>
struct CHT {
    vector<pair<T, T>> lines;
    F comp;
    int head;
    CHT(T _e, F _comp) : comp(_comp), head(0) { lines.emplace_back(0, _e); };

    bool check(pair<T, T> l1, pair<T, T> l2, pair<T, T> l3) {
        if (l1 < l3) swap(l1, l3);
        return (l3.second - l2.second) * (l2.first - l1.first) >=
               (l2.second - l1.second) * (l3.first - l2.first);
    }

    void add(T a, T b) {
        pair<T, T> line(a, b);
        while (lines.size() >= 2 &&
               check(*(lines.end() - 2), lines.back(), line))
            lines.pop_back();
        lines.emplace_back(line);
    }

    T f(int i, T x) { return lines[i].first * x + lines[i].second; }
    T f(pair<T, T> line, T x) { return line.first * x + line.second; }

    T get(T x) {
        // while(lines.size() >= 2 + head && comp(f(head, x), f(head + 1, x))){
        //     head++;
        // }
        // return f(head, x);
        int low = -1, high = lines.size() - 1;
        while (high - low > 1) {
            int mid = (high + low) / 2;
            if (comp(f(mid, x), f(mid + 1, x)))
                low = mid;
            else
                high = mid;
        }
        return f(high, x);
    }
};
