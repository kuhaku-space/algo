#include "template/template.hpp"

template <class T>
struct Sum {
    using value_type = T;
    static constexpr T id = 0;
    static T op(T l, T r) { return l + r; }
};

template <class T>
struct Min {
    using value_type = T;
    static constexpr T id = numeric_limits<T>::max();
    static T op(T l, T r) { return min(l, r); }
};

template <class T>
struct Max {
    using value_type = T;
    static constexpr T id = numeric_limits<T>::min();
    static T op(T l, T r) { return max(l, r); }
};

struct Add {
    template <class T, class U>
    static T f(U val, T x) {
        return val + x;
    }
};

struct Update {
    template <class T, class U>
    static T f(U val, T x) {
        return val;
    }
};

struct Chmin {
    template <class T, class U>
    static T f(U val, T x) {
        return min((T)val, x);
    }
};

struct Chmax {
    template <class T, class U>
    static T f(U val, T x) {
        return max((T)val, x);
    }
};
