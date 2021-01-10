#include "_base.hpp"

// https://github.com/ei1333/library/blob/master/math/combinatorics/mod-int.cpp

template <int mod>
struct ModInt {
    int64_t x;

    ModInt() : x(0) {}

    ModInt(int64_t y) : x(y >= 0 ? y % mod : (mod - (-y) % mod) % mod) {}

    ModInt &operator+=(const ModInt &rhs) {
        if ((x += rhs.x) >= mod) x -= mod;
        return *this;
    }
    ModInt &operator-=(const ModInt &rhs) {
        if ((x += mod - rhs.x) >= mod) x -= mod;
        return *this;
    }
    ModInt &operator*=(const ModInt &rhs) {
        x = (int)(1LL * x * rhs.x % mod);
        return *this;
    }
    ModInt &operator/=(const ModInt &rhs) {
        *this *= rhs.inverse();
        return *this;
    }

    ModInt &operator++() {
        if ((++x) >= mod) x -= mod;
        return *this;
    }
    ModInt operator++(int) {
        ModInt tmp(*this);
        operator++();
        return tmp;
    }
    ModInt &operator--() {
        if ((x += mod - 1) >= mod) x -= mod;
        return *this;
    }
    ModInt operator--(int) {
        ModInt tmp(*this);
        operator--();
        return tmp;
    }

    ModInt operator-() const { return ModInt(-x); }
    ModInt operator+(const ModInt &rhs) const { return ModInt(*this) += rhs; }
    ModInt operator-(const ModInt &rhs) const { return ModInt(*this) -= rhs; }
    ModInt operator*(const ModInt &rhs) const { return ModInt(*this) *= rhs; }
    ModInt operator/(const ModInt &rhs) const { return ModInt(*this) /= rhs; }

    bool operator==(const ModInt &rhs) const { return x == rhs.x; }
    bool operator!=(const ModInt &rhs) const { return x != rhs.x; }

    ModInt inverse() const {
        int a = x, b = mod, u = 1, v = 0, t;
        while (b > 0) {
            t = a / b;
            swap(a -= t * b, b);
            swap(u -= t * v, v);
        }
        return ModInt(u);
    }

    ModInt pow(int64_t n) const {
        ModInt res(1), mul(x);
        for (; n > 0; n >>= 1) {
            if (n & 1) res *= mul;
            mul *= mul;
        }
        return res;
    }

    void pow_self(int64_t n) {
        ModInt tmp = pow(n);
        swap(*this, tmp);
    }

    friend ostream &operator<<(ostream &os, const ModInt &rhs) {
        return os << rhs.x;
    }

    friend istream &operator>>(istream &is, ModInt &rhs) {
        int64_t t;
        is >> t;
        rhs = ModInt<mod>(t);
        return (is);
    }

    int to_int() const { return x; }

    static int get_mod() { return mod; }
};
using Mint = ModInt<MOD>;
