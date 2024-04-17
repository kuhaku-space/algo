#include <algorithm>
#include <functional>
#include <queue>
#include <vector>

/**
 * @brief slope trick
 *
 * @tparam T
 */
template <class T>
struct slope_trick {
    T min_f;
    std::priority_queue<T> l;
    std::priority_queue<T, std::vector<T>, std::greater<>> r;

    slope_trick() : min_f(), l(), r() {}

    T get_x() { return l.top(); }
    T get() { return min_f; }
    T get_y() { return get(); }

    /**
     * @brief Add f(x) = a
     *
     * @param a
     */
    void add(T a) { min_f += a; }

    /**
     * @brief Add f(x) = max(0, x - a)
     *
     * @param a
     */
    void add_f(T a) {
        if (!l.empty()) min_f += std::max(T(), l.top() - a);
        l.emplace(a);
        auto x = l.top();
        l.pop();
        r.emplace(x);
    }

    /**
     * @brief Add f(x) = max(0, a - x)
     *
     * @param a
     */
    void add_g(T a) {
        if (!r.empty()) min_f += std::max(T(), a - r.top());
        r.emplace(a);
        auto x = r.top();
        r.pop();
        l.emplace(x);
    }

    /**
     * @brief Add f(x) = abs(x - a) = max(0, x - a) + max(0, a - x)
     *
     * @param a
     */
    void add_abs(T a) {
        add_f(a);
        add_g(a);
    }

    void min_l() { r = std::priority_queue<T, std::vector<T>, std::greater<>>(); }
    void min_r() { l = std::priority_queue<T>(); }
};
