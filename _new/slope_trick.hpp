#include "_base.hpp"

template <class T, class U>
struct slope_trick {
    U min_f;
    priority_queue<T> l;
    priority_queue<T, vector<T>, greater> r;

    slope_trick() : min_f(), l(), r() {}

    U get() { return min_f; }

    // Add f(x) = a
    void add(U a) { min_f += a; }

    // Add f(x) = max(0, x - a)
    void add_f(T a) {
        min_f += max(U(), l.top() - a);
        l.push(a);
        auto x = l.top();
        l.pop();
        r.push(x);
    }

    // Add f(x) = max(0, a - x)
    void add_g(U a) {
        min_f += max(U(), a - r.top());
        r.push(a);
        auto x = r.top();
        r.pop();
        l.push(x);
    }

    // Add f(x) = abs(x - a)
    void add_abs(U a) {
        add_f(a);
        add_g(a);
    }

    void min_l() { r = priority_queue<T, vector<T>, greater>(); }
    void min_r() { l = priority_queue<T>(); }
};
