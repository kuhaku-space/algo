#include "template/template.hpp"

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

    T get_x() { return this->l.top(); }
    T get() { return this->min_f; }
    T get_y() { return this->get(); }

    /**
     * @brief Add f(x) = a
     *
     * @param a
     */
    void add(T a) { this->min_f += a; }

    /**
     * @brief Add f(x) = max(0, x - a)
     *
     * @param a
     */
    void add_f(T a) {
        if (!this->l.empty()) this->min_f += std::max(T(), this->l.top() - a);
        this->l.emplace(a);
        auto x = this->l.top();
        this->l.pop();
        this->r.emplace(x);
    }

    /**
     * @brief Add f(x) = max(0, a - x)
     *
     * @param a
     */
    void add_g(T a) {
        if (!this->r.empty()) this->min_f += std::max(T(), a - this->r.top());
        this->r.emplace(a);
        auto x = this->r.top();
        this->r.pop();
        this->l.emplace(x);
    }

    /**
     * @brief Add f(x) = abs(x - a) = max(0, x - a) + max(0, a - x)
     *
     * @param a
     */
    void add_abs(T a) {
        this->add_f(a);
        this->add_g(a);
    }

    void min_l() { this->r = std::priority_queue<T, std::vector<T>, std::greater<>>(); }
    void min_r() { this->l = std::priority_queue<T>(); }
};
