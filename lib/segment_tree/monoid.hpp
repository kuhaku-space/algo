#pragma once
#include <algorithm>
#include <limits>
#include <utility>

template <class T>
struct Add {
    using value_type = T;
    static constexpr T id() { return T(); }
    static constexpr T op(const T &lhs, const T &rhs) { return lhs + rhs; }

    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return lhs + rhs;
    }
};

template <class T>
struct Mul {
    using value_type = T;
    static constexpr T id() { return T(1); }
    static constexpr T op(const T &lhs, const T &rhs) { return lhs * rhs; }

    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return lhs * rhs;
    }
};

template <class T>
struct And {
    using value_type = T;
    static constexpr T id() { return std::numeric_limits<T>::max(); }
    static constexpr T op(const T &lhs, const T &rhs) { return lhs & rhs; }

    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return lhs & rhs;
    }
};

template <class T>
struct Or {
    using value_type = T;
    static constexpr T id() { return T(); }
    static constexpr T op(const T &lhs, const T &rhs) { return lhs | rhs; }

    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return lhs | rhs;
    }
};

template <class T>
struct Xor {
    using value_type = T;
    static constexpr T id() { return T(); }
    static constexpr T op(const T &lhs, const T &rhs) { return lhs ^ rhs; }

    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return lhs ^ rhs;
    }
};

template <class T>
struct Min {
    using value_type = T;
    static constexpr T id() { return std::numeric_limits<T>::max(); }
    static constexpr T op(const T &lhs, const T &rhs) { return std::min(lhs, rhs); }

    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return std::min((U)lhs, rhs);
    }
};

template <class T>
struct Max {
    using value_type = T;
    static constexpr T id() { return std::numeric_limits<T>::lowest(); }
    static constexpr T op(const T &lhs, const T &rhs) { return std::max(lhs, rhs); }

    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return std::max((U)lhs, rhs);
    }
};

template <class T>
struct Update {
    using value_type = T;
    static constexpr T id() { return std::numeric_limits<T>::max(); }
    static constexpr T op(const T &lhs, const T &rhs) { return lhs == Update::id ? rhs : lhs; }

    template <class U>
    static constexpr U f(T lhs, U rhs) {
        return lhs == Update::id ? rhs : lhs;
    }
};

template <class T>
struct Affine {
    using P = std::pair<T, T>;
    using value_type = P;
    static constexpr P id() { return P(1, 0); }
    static constexpr P op(P lhs, P rhs) {
        return {lhs.first * rhs.first, lhs.first * rhs.second + lhs.second};
    }
};

template <class M>
struct Rev {
    using T = typename M::value_type;
    using value_type = T;
    static constexpr T id() { return M::id; }
    static constexpr T op(T lhs, T rhs) { return M::op(rhs, lhs); }
};
