#include "fft/ntt.hpp"
#include "math/modint.hpp"
#include "template/template.hpp"

template <class mint>
struct formal_power_series : std::vector<mint> {
    using fps = formal_power_series;

    formal_power_series(std::vector<T> &&v) : std::vector<mint>(v) {}
    formal_power_series(const std::vector<T> &v) : std::vector<mint>(v) {}

    constexpr fps &operator+=(const mint &v) {
        if (this->empty()) this->resize(1);
        (*this)[0] += v;
        return *this;
    }
    constexpr fps &operator+=(const fps &f) {
        if (f.size() > this->size()) this->resize(f.size());
        for (int i = 0; i < (int)f.size(); ++i) (*this)[i] += f[i];
        return this->normalize();
    }
    constexpr fps &operator-=(const mint &v) {
        if (this->empty()) this->resize(1);
        (*this)[0] -= v;
        return *this;
    }
    constexpr fps &operator-=(const fps &f) {
        if (f.size() > this->size()) this->resize(f.size());
        for (int i = 0; i < (int)f.size(); ++i) (*this)[i] -= f[i];
        return this->normalize();
    }
    constexpr fps &operator*=(const mint &v) {
        for (int i = 0; i < (int)this->size(); ++i) (*this)[i] *= v;
        return *this;
    }
    constexpr fps &operator*=(const fps &f) { return *this = convolution((*this), f); }
    constexpr fps &operator/=(const mint &v) {
        assert(v != 0);
        mint iv = modinv(v);
        for (int i = 0; i < (int)this->size(); ++i) (*this)[i] *= iv;
        return *this;
    }
    constexpr fps &operator<<=(int x) {
        fps res(x, 0);
        res.insert(res.end(), begin(*this), end(*this));
        return *this = res;
    }
    constexpr fps &operator>>=(int x) {
        fps res;
        res.insert(res.end(), begin(*this) + x, end(*this));
        return *this = res;
    }

    constexpr fps operator+(const mint &v) const { return fps(*this) += v; }
    constexpr fps operator+(const fps &f) const { return fps(*this) += f; }
    constexpr fps operator-(const mint &v) const { return fps(*this) -= v; }
    constexpr fps operator-(const fps &f) const { return fps(*this) -= f; }
    constexpr fps operator*(const mint &v) const { return fps(*this) *= v; }
    constexpr fps operator*(const fps &f) const { return fps(*this) *= f; }
    constexpr fps operator/(const mint &v) const { return fps(*this) /= v; }
    constexpr fps operator<<(int x) const { return fps(*this) <<= x; }
    constexpr fps operator>>(int x) const { return fps(*this) >>= x; }

    constexpr fps operator+() const { return fps(*this); }
    constexpr fps operator-() const {
        fps res = *this;
        for (int i = 0; i < (int)res.size(); ++i) res[i] = -res[i];
        return res;
    }

    constexpr fps pre(int sz) const {
        return fps(std::begin(*this), std::begin(*this) + std::min((int)this->size(), sz));
    }
    constexpr fps inv(int deg) {
        assert((*this)[0] != 0);
        if (deg < 0) deg = (int)v.size();
        fps res({mint(1) / (*this)[0]});
        for (int i = 1; i < deg; i <<= 1) {
            res = (res + res - res * res * this->pre(i << 1)).pre(i << 1);
        }
        res.resize(deg);
        return res;
    }
    constexpr fps inv() { return inv(v.size()); }
};
