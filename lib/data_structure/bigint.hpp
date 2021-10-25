#include "fft/ntt.hpp"
#include "template/template.hpp"

/*
 * verify:
 * https://onlinejudge.u-aizu.ac.jp/problems/NTL_2_A 21/03/02
 * https://onlinejudge.u-aizu.ac.jp/problems/NTL_2_B 21/03/02
 * https://onlinejudge.u-aizu.ac.jp/problems/NTL_2_F 21/03/02
 */

struct BigInt {
    vector<int> data;
    bool is_negative;

    BigInt() : data(1), is_negative() {}
    BigInt(string s) : data(s.size()), is_negative(false) {
        if (s[0] == '-') is_negative = true;
        reverse(s.begin(), s.end());
        if (is_negative) s.pop_back(), data.pop_back();
        for (int i = 0; i < s.size(); ++i) { data[i] = s[i] - '0'; }
    }

    BigInt &operator+=(const BigInt &rhs) {
        if (is_negative ^ rhs.is_negative) return *this -= -rhs;
        int n = max(size(), rhs.size());
        data.resize(n, 0);
        for (int i = 0; i < rhs.size(); ++i) data[i] += rhs.data[i];
        format();
        return *this;
    }
    BigInt &operator-=(const BigInt &rhs) {
        if (is_negative ^ rhs.is_negative) return *this += -rhs;
        bool f = abs_less(rhs);
        int n = max(size(), rhs.size());
        data.resize(n, 0);
        for (int i = 0; i < rhs.size(); ++i) data[i] -= rhs.data[i];
        if (f) {
            is_negative = !is_negative;
            for (auto &i : data) i = -i;
        }
        format();
        return *this;
    }
    BigInt &operator*=(const BigInt &rhs) {
        NTT<469762049, 3> ntt;  // 2^26 * 7 + 1
        ntt.convolution_self(data, rhs.data);
        is_negative ^= rhs.is_negative;
        format();
        return *this;
    }
    BigInt &operator/=(const BigInt &rhs) {
        assert(!rhs.is_zero());
        BigInt cp = *this;
        cp.is_negative = false;
        bool flg = this->is_negative ^ rhs.is_negative;
        BigInt x = rhs;
        this->is_negative = false;
        x.is_negative = false;
        if (*this < x) return *this = BigInt();
        NTT<469762049, 3> ntt;  // 2^26 * 7 + 1
        int sum = rhs.size();
        for (int i = 0; i < 20; ++i) {
            int len = x.size();
            BigInt a(string("1") + string(len, '0'));
            BigInt b = a + a - x;
            ntt.convolution_self(data, b.data);
            ntt.convolution_self(x.data, b.data);
            format();
            x.format();
            sum += len;
            int max_len = max(this->size(), x.size());
            if (max_len > 1 << 15) {
                max_len -= 1 << 15;
                *this >>= max_len;
                x >>= max_len;
                sum -= max_len;
            }
        }
        *this >>= sum;
        if ((*this + BigInt("1")) * rhs.abs() <= cp) *this += BigInt("1");
        this->is_negative = flg;
        format();
        return *this;
    }
    BigInt &operator>>=(int rhs) {
        data.erase(data.begin(), data.begin() + rhs);
        return *this;
    }

    BigInt operator-() const {
        BigInt res = *this;
        if (!res.is_zero()) res.is_negative = !res.is_negative;
        return res;
    }
    BigInt operator+(const BigInt &rhs) const { return BigInt(*this) += rhs; }
    BigInt operator-(const BigInt &rhs) const { return BigInt(*this) -= rhs; }
    BigInt operator*(const BigInt &rhs) const { return BigInt(*this) *= rhs; }
    BigInt operator/(const BigInt &rhs) const { return BigInt(*this) /= rhs; }

    bool operator<(const BigInt &rhs) const {
        if (is_negative ^ rhs.is_negative) return is_negative;
        if (size() ^ rhs.size()) return size() < rhs.size();
        for (int i = size() - 1; i >= 0; --i) {
            if (data[i] ^ rhs.data[i]) return data[i] < rhs.data[i];
        }
        return false;
    }
    bool operator>(const BigInt &rhs) const { return rhs < *this; }
    bool operator<=(const BigInt &rhs) const { return !(*this > rhs); }
    bool operator>=(const BigInt &rhs) const { return !(*this < rhs); }

    friend ostream &operator<<(ostream &os, const BigInt &rhs) {
        string s;
        for (auto i : rhs.data) s.push_back(char(i + '0'));
        if (rhs.is_negative) s.push_back('-');
        reverse(s.begin(), s.end());
        os << s;
        return os;
    }

    friend istream &operator>>(istream &is, BigInt &rhs) {
        string s;
        is >> s;
        rhs = BigInt(s);
        return is;
    }

    inline int size() const { return data.size(); }

    int back() const {
        assert(data.size() > 0);
        return data.back();
    }

    inline bool is_zero() const { return data.size() == 1 && data[0] == 0; }

    void format() {
        data.emplace_back(0);
        for (int i = 0; i < size() - 1; ++i) {
            data[i + 1] += data[i] / 10;
            data[i] %= 10;
            if (data[i] < 0) --data[i + 1], data[i] += 10;
        }
        while (size() > 1 && back() == 0) data.pop_back();
        if (is_zero()) is_negative = false;
    }

    BigInt abs() const {
        if (!this->is_negative) return *this;
        return -(*this);
    }
    bool abs_less(const BigInt &rhs) {
        if (size() ^ rhs.size()) return size() < rhs.size();
        for (int i = size() - 1; i >= 0; --i) {
            if (data[i] ^ rhs.data[i]) return data[i] < rhs.data[i];
        }
        return false;
    }
};
