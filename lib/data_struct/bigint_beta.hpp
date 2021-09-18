#include "_base.hpp"
#include "fft/ntt.hpp"

/*
 * verify:
 * https://onlinejudge.u-aizu.ac.jp/problems/NTL_2_A 21/03/02
 * https://onlinejudge.u-aizu.ac.jp/problems/NTL_2_B 21/03/02
 * https://onlinejudge.u-aizu.ac.jp/problems/NTL_2_F 21/03/02
 */

struct BigInt {
    vector<int> data;

    BigInt() {}
    BigInt(string s) : data(s.size()) {
        bool flg = s[0] == '-';
        reverse(s.begin(), s.end());
        if (flg) s.pop_back(), data.pop_back();
        for (int i = 0; i < s.size(); ++i) {
            if (flg)
                data[i] = -(s[i] - '0');
            else
                data[i] = s[i] - '0';
        }
    }

    BigInt &operator+=(const BigInt &rhs) {
        int n = max(size(), rhs.size());
        data.resize(n, 0);
        for (int i = 0; i < rhs.size(); ++i) data[i] += rhs.data[i];
        format();
        return *this;
    }
    BigInt &operator-=(const BigInt &rhs) {
        int n = max(size(), rhs.size());
        data.resize(n, 0);
        for (int i = 0; i < rhs.size(); ++i) data[i] -= rhs.data[i];
        format();
        return *this;
    }
    BigInt &operator*=(const BigInt &rhs) {
        const int mod = 469762049;
        NTT<469762049, 3> ntt;  // 2^26 * 7 + 1
        ntt.convolution_self(data, rhs.data);
        for (int i = 0; i < size(); ++i) {
            if (data[i] >= mod / 2) data[i] -= mod;
        }
        format();
        return *this;
    }

    BigInt operator-() const {
        BigInt res(*this);
        for (int i = 0; i < res.size(); ++i) res.data[i] = -res.data[i];
        return res;
    }
    BigInt operator+(const BigInt &rhs) const { return BigInt(*this) += rhs; }
    BigInt operator-(const BigInt &rhs) const { return BigInt(*this) -= rhs; }
    BigInt operator*(const BigInt &rhs) const { return BigInt(*this) *= rhs; }

    bool operator<(const BigInt &rhs) const {
        if (is_negative() ^ rhs.is_negative()) return back() < rhs.back();
        if (size() ^ rhs.size()) return size() < rhs.size();
        for (int i = size() - 1; i >= 0; --i) {
            if (data[i] ^ rhs.data[i]) return data[i] < rhs.data[i];
        }
        return false;
    }

    friend ostream &operator<<(ostream &os, const BigInt &rhs) {
        string s;
        bool flg = rhs.is_negative();
        for (auto i : rhs.data) {
            if (flg)
                s.push_back(char('0' - i));
            else
                s.push_back(char('0' + i));
        }
        if (rhs.is_negative()) s.push_back('-');
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

    bool is_negative() const { return back() < 0; }

    inline bool is_zero() const { return data.size() == 1 && data[0] == 0; }

    void format() {
        while (size() > 1 && back() == 0) data.pop_back();
        bool flg = is_negative();
        data.emplace_back(0);
        for (int i = 0; i < size() - 1; ++i) {
            data[i + 1] += data[i] / 10;
            data[i] %= 10;
            if (flg && data[i] > 0) ++data[i + 1], data[i] -= 10;
            if (!flg && data[i] < 0) --data[i + 1], data[i] += 10;
        }
        while (size() > 1 && back() == 0) data.pop_back();
    }
};
