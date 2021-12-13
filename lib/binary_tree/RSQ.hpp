#include "binary_tree/segment_tree_virtual.hpp"
#include "template/template.hpp"

template <class T>
struct RSMQ {
    struct segment_tree_max : segment_tree<pair<T, T>> {
        segment_tree_max(int _n, pair<T, T> _e) : segment_tree<pair<T, T>>(_n, _e) {}
        pair<T, T> op(pair<T, T> a, pair<T, T> b) const {
            return make_pair(max(a.first, a.second + b.first), a.second + b.second);
        }
        pair<T, T> f(pair<T, T> val, pair<T, T> x) {
            T y = val.second + x.second;
            return make_pair(y, y);
        }
    };

    segment_tree_max st;

    RSMQ(int _n, T _e) : st(_n + 1, make_pair(_e, T(0))) {}

    void apply(int k, T val) { this->apply(k, k + 1, val); }
    void apply(int a, int b, T val) {
        this->st.add(a, make_pair(val, val));
        this->st.add(b, make_pair(-val, -val));
    }
    void add(int k, T val) { this->apply(k, k + 1, val); }
    void add(int a, int b, T val) { this->apply(a, b, val); }

    T prod(int a, int b) { return this->st.prod(0, a).second + this->st.prod(a, b).first; }

    T at(int k) { return this->st.prod(0, k).second; }
    T get(int k) { return this->at(k); }
};

template <class T>
struct RSmQ {
    struct segment_tree_min : segment_tree<pair<T, T>> {
        segment_tree_min(int _n, pair<T, T> _e) : segment_tree<pair<T, T>>(_n, _e) {}
        pair<T, T> op(pair<T, T> a, pair<T, T> b) const {
            return make_pair(min(a.first, a.second + b.first), a.second + b.second);
        }
        pair<T, T> f(pair<T, T> val, pair<T, T> x) {
            T y = val.second + x.second;
            return make_pair(y, y);
        }
    };
    segment_tree_min st;

    RSmQ(int _n, T _e) : st(_n + 1, make_pair(_e, T(0))) {
        this->st.init(_n + 1, make_pair(T(0), T(0)));
    }

    void apply(int k, T val) { this->apply(k, k + 1, val); }
    void apply(int a, int b, T val) {
        this->st.apply(a, make_pair(val, val));
        this->st.apply(b, make_pair(-val, -val));
    }
    void add(int k, T val) { this->apply(k, k + 1, val); }
    void add(int a, int b, T val) { this->apply(a, b, val); }

    T prod(int a, int b) { return this->st.prod(0, a).second + this->st.prod(a, b).first; }

    T at(int k) { return this->st.prod(0, k + 1).second; }
    T get(int k) { return this->at(k); }
};
