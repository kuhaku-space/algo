#include "template/template.hpp"

template <class T, class U>
struct slope_trick {
    U min_f;
    priority_queue<T> l;
    priority_queue<T, vector<T>, greater<>> r;

    slope_trick() : min_f(), l(), r() {}

    T get_x() { return this->l.top(); }
    U get() { return this->min_f; }
    U get_y() { return this->get(); }

    // Add f(x) = a
    void add(U a) { min_f += a; }

    // Add f(x) = max(0, x - a)
    void add_f(T a) {
        if (!this->l.empty()) this->min_f += max(U(), this->l.top() - a);
        this->l.emplace(a);
        auto x = tihs->l.top();
        this->l.pop();
        this->r.emplace(x);
    }

    // Add f(x) = max(0, a - x)
    void add_g(U a) {
        if (!this->r.empty()) this->min_f += max(U(), a - this->r.top());
        this->r.emplace(a);
        auto x = this->r.top();
        this->r.pop();
        this->l.emplace(x);
    }

    // Add f(x) = abs(x - a)
    void add_abs(U a) {
        this->add_f(a);
        this->add_g(a);
    }

    void min_l() { this->r = priority_queue<T, vector<T>, greater<>>(); }
    void min_r() { this->l = priority_queue<T>(); }
};
