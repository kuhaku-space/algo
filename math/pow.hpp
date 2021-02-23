#include "_base.hpp"

template <class T>
T power(T a, int64_t n) {
    T res(1), mul(a);
    for (; n > 0; n >>= 1) {
        if (n & 1) res *= mul;
        mul *= mul;
    }
    return res;
}

int64_t pow_int(int64_t a, int64_t n) {
    assert(n >= 0);
    int64_t res = 1, mul = a;
    for (; n > 0; n >>= 1) {
        if (n & 1) res *= mul;
        mul *= mul;
    }
    return res;
}

int64_t inv_mod(int64_t a, int64_t mod) {
    int64_t b = mod, u = 1, v = 0, t;
    while (b > 0) {
        t = a / b;
        swap(a -= t * b, b);
        swap(u -= t * v, v);
    }
    return u >= 0 ? u % mod : (mod - (-u) % mod) % mod;
}

int64_t pow_mod(int64_t a, int64_t n, int64_t mod) {
    // if (n < 0) return inv_mod(pow_mod(a, -n, mod), mod);
    int64_t res = 1, mul = a;
    for (; n > 0; n >>= 1) {
        if (n & 1) (res *= mul) %= mod;
        (mul *= mul) %= mod;
    }
    return res;
}
